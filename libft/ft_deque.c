/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 21:19:22 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/02 04:01:06 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**############DMCA(by lkaba)#############################################
**This is an  amazing thing I'm making I called it the dynamic multitype
**circular array,  he can hold  any type even itself what is awesome.
**He can increase it own size, add  and remove items from
**the front and front the rear;
**Another amazing thing it's circulare Incredible Alhamdullah;
**with this array I can Implement a stack, or a queue or a  deque
**I can put a queue Inside the stack vice versa; And its faster because
**the data is store in a contigius block of memory
**the stucture of the algorithm it's self Is a perfection because it's
**It' based on mathematics formula.
**"s" : is the input data size Ex: size of "int" or "char *"
**"max": is the maximun size of the array
*/

uint8_t		ft_dq_grow(t_deque *dq)
{
	void		*ptr;
	size_t		i;
	size_t		j;

	dq->capacity *= 2;
	if (!(ptr = (void *)malloc(dq->capacity)))
		return (0);
	ft_memset((uint8_t *)ptr, 0, dq->capacity);
	if (dq->tab && (i = -1))
	{
		j = (dq->front == 0) ? dq->max : dq->front;
		while (++i < j)
			ft_memcpy((((uint8_t *)ptr) + i * dq->s),
				(((uint8_t *)dq->tab) + i * dq->s), dq->s);
		if (dq->front && dq->front != U32)
		{
			i = dq->max;
			while (--i >= dq->front)
				ft_memcpy((((uint8_t *)ptr) + (i + dq->max) * dq->s),
					(((uint8_t *)dq->tab) + i * dq->s), dq->s);
		}
	}
	free(dq->tab);
	dq->max ? (dq->tab = ptr) && (dq->max *= 2) : 0;
	return (1);
}

/*
**push_rear
*/

void		ft_enqueue_rear_dq(void *data, t_deque *dq)
{
	if (is_dq_empty(dq))
	{
		dq->front = 0;
		dq->rear = 0;
	}
	else
		dq->rear = (dq->rear + 1) % dq->max;
	if (dq->rear && dq->rear == dq->front)
	{
		if (!ft_dq_grow(dq))
		{
			ft_putendl("ft_darray_grow operation fail\n");
			return ;
		}
		if (dq->front)
			dq->front += dq->max / 2;
	}
	ft_memcpy(((uint8_t *)dq->tab) + dq->rear * dq->s, data, dq->s);
}

/*
**push_front
*/

void		ft_enqueue_front_dq(void *data, t_deque *dq)
{
	if (is_dq_empty(dq))
	{
		dq->front = 0;
		dq->rear = 0;
	}
	dq->f = !dq->front ? dq->max - 1 : dq->front - 1;
	if (dq->f == dq->rear)
	{
		if (!ft_dq_grow(dq))
		{
			ft_putendl("ft_darray_grow operation fail");
			return ;
		}
		dq->front = dq->f + dq->max / 2;
		ft_memcpy(((uint8_t *)dq->tab) + dq->front * dq->s, data, dq->s);
	}
	else
	{
		dq->front = dq->f;
		ft_memcpy(((uint8_t *)dq->tab) + dq->front * dq->s, data, dq->s);
	}
	dq->f = 0;
}

/*
**pop_rear
*/

void		*dequeue_rear(t_deque *dq)
{
	void	*tmp;

	if (is_dq_empty(dq) && (ft_printf("Is empty\n")))
		return (0);
	tmp = (void *)malloc(dq->s);
	if (dq->front == dq->rear)
	{
		ft_memcpy(tmp, ((uint8_t *)dq->tab) + dq->rear * dq->s, dq->s);
		dq->rear = -1;
		dq->front = -1;
	}
	else
	{
		ft_memcpy(tmp, ((uint8_t *)dq->tab) + dq->rear * dq->s, dq->s);
		dq->rear = (dq->rear - 1) % dq->max;
	}
	return (tmp);
}

/*
**pop from the front
*/

void		*dequeue_front(t_deque *dq)
{
	void	*tmp;

	if (is_dq_empty(dq) && (ft_printf("Is empty\n")))
		return (0);
	tmp = (void *)malloc(dq->s);
	if (dq->front == dq->rear)
	{
		ft_memcpy(tmp, ((uint8_t *)dq->tab) + dq->front * dq->s, dq->s);
		dq->rear = -1;
		dq->front = -1;
	}
	else
	{
		ft_memcpy(tmp, ((uint8_t *)dq->tab) + dq->front * dq->s, dq->s);
		dq->front = (dq->front + 1) % dq->max;
	}
	return (tmp);
}
