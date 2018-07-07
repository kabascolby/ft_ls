/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 21:25:18 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/07 11:20:00 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_tree	*t_new_node(t_tree *r, char *s)
{
	t_tree	*node;

	if (!(node = (t_tree *)malloc(sizeof(t_tree))))
		return(0);
	node->data = s;
	if (lstat(s, &r->buf) != 0)
		return (0);
	node->left = NULL;
	node->right= NULL;
	return (node);
}

t_tree	*insert_tree(t_tree *r, char *s)
{
	//ft_printf("%s\n", s);
	if (r == NULL)
	{
			//printf("kfdkffkjdjf\n");
		r = t_new_node(r, s);
	}
	else if (ft_strcmp(r->data, s) > 0)
		r->left = insert_tree(r->left, s);
	else
		r->right = insert_tree(r->right, s);
	return(r);
}

t_tree	*insert_by_flags(t_ls *ls, char *s)
{
	t_tree *temp;
	
	temp = t_new_node(ls->r, s);
	if (ls->r == NULL)
	{
		ls->r = temp;
	}
	else if(compare_flags(ls->r, temp) > 0)
		ls->r->left = insert_by_flags(ls, s);
	else
		ls->r->right = insert_by_flags(ls, s);
	return(ls->r);
}

void	inorder_print(t_tree *r,  char *info1, char *info2)
{
	if (!r)
		return;
	inorder_print(r->left, info1, info2);
	ft_printf("%s%s%s\n", info1, r->data, info2);
	inorder_print(r->right, info1, info2);
}

void	deallocat_tree(t_tree *r)
{
	if (!r)
		return;
	deallocat_tree(r->left);
	deallocat_tree(r->right);
	free(r);
}