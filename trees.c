/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 21:25:18 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/04 23:28:46 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_tree	*t_new_node(char *s)
{
	t_tree	*node;

	if (!(node = (t_tree *)malloc(sizeof(t_tree))))
		return(0);
	node->data = ft_strdup(s);
	node->cpt = 0;
	node->left = NULL;
	node->right= NULL;
	return (node);
}

t_tree	*insert_tree(t_tree *r, char *s)
{
	if (r == NULL)
	{
		r = t_new_node(s);
	}
	else if (ft_strcmp(r->data, s) > 0)
		r->left = insert_tree(r->left, s);
	else
		r->right = insert_tree(r->right, s);
	return(r);
}

t_tree	*insert_tree_rev(t_tree *r, char *s)
{
	if (r == NULL)
	{
		r = t_new_node(s);
	}
	else if (ft_strcmp(r->data, s) <= 0)
		r->left = insert_tree(r->left, s);
	else
		r->right = insert_tree(r->right, s);
	return(r);
}

/* void traverse_dir(void (*flags[])(char *s))
{
	printf("i'm here\n");
} */

void	inorder_print(t_tree *r)
{
	if (!r)
		return;
	inorder_print(r->left);
	printf("%s\n",r->data);
	inorder_print(r->right);
}
