/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:01:21 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/02 04:06:21 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEQUE_H
# define FT_DEQUE_H
# include "libft.h"
# define U32 4294967295

typedef struct	s_deque
{
	void			*tab;
	uint32_t		front;
	uint32_t		rear;
	uint32_t		len;
	uint32_t		max;
	uint32_t		capacity;
	uint32_t		f;
	uint32_t		s;
}				t_deque;

t_deque			nit_deque(uint32_t length, uint8_t data_t_size);
uint8_t			ft_dq_grow(t_deque *dq);
void			ft_enqueue_rear_dq(void *data, t_deque *dq);
void			ft_enqueue_front_dq(void *data, t_deque *dq);
void			*dequeue_rear(t_deque *dq);
void			*dequeue_front(t_deque *dq);
uint8_t			is_dq_empty(t_deque *dq);
void			*dq_peak_rear(t_deque *dq);
void			*dq_peek_front(t_deque *dq);
#endif
