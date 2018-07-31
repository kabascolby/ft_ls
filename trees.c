/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 21:25:18 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 19:52:31 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_tree	*t_new_node(char *path, char *name)
{
	t_tree	*node;

	if (!(node = (t_tree *)malloc(sizeof(t_tree))))
		return (0);
	node->path = ft_strdup(path);
	node->name = ft_strdup(name);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree	*insert_by_name(t_tree *r, t_tree *node)
{
	if (r == NULL)
	{
		r = node;
	}
	else if (compare_by_name(r, node))
		r->left = insert_by_name(r->left, node);
	else
		r->right = insert_by_name(r->right, node);
	return (r);
}

t_tree	*insert_by_flags(t_ls *ls, t_tree *r, t_tree *node)
{
	if (r == NULL)
		r = node;
	else if (ls->compare(r, node) > 0)
		r->left = insert_by_flags(ls, r->left, node);
	else
		r->right = insert_by_flags(ls, r->right, node);
	return (r);
}

t_tree	*insert_reverse_flags(t_ls *ls, t_tree *r, t_tree *node)
{
	if (r == NULL)
		r = node;
	else if (ls->compare(r, node) <= 0)
		r->left = insert_reverse_flags(ls, r->left, node);
	else
		r->right = insert_reverse_flags(ls, r->right, node);
	return (r);
}

void	deallocat_tnode(t_tree *r)
{
	if (r)
	{
		free(r->name);
		free(r->path);
		free(r);
	}
}
