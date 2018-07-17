/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 21:25:18 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/17 06:55:22 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_tree	*t_new_node(char *path, char *name)
{
	t_tree	*node;

	if (!(node = (t_tree *)malloc(sizeof(t_tree))))
		return(0);
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
	else if(compare_by_name(r, node))
		r->left = insert_by_name(r->left, node);
	else
		r->right = insert_by_name(r->right, node);
	return(r);
}

t_tree	*insert_by_flags(t_ls *ls, t_tree *r, t_tree *node)
{
	if (r == NULL)
		r = node;
	else if (ls->compare(r, node) > 0)
		r->left = insert_by_flags(ls, r->left , node);
	else
		r->right = insert_by_flags(ls, r->right, node);
	return(r);
}

void	inorder_print(t_tree *r,  char *info1, char *info2)
{
	if (!r)
		return;
	inorder_print(r->left, info1, info2);
	printf("%s%s%s\n", info1, r->name, info2);
	inorder_print(r->right, info1, info2);
}

void	deallocat_tree(t_tree *r)
{
	if (!r)
		return;
	deallocat_tree(r->left);
	free(r->name);
	free(r->path);
	deallocat_tree(r->right);
	free(r);
}