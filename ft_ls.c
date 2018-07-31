/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 16:40:07 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 18:49:34 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_tree		*ls_dir(t_ls *ls, char *name)
{
	static char		path[1025];
	DIR				*sd;
	struct dirent	*sdir;
	t_tree			*node;
	t_tree			*r;

	r = NULL;
	ls->total = 0;
	sd = NULL;
	if ((access(name, X_OK) == 0) &&
		(access(name, R_OK) == 0) && (sd = opendir(name)))
		while ((sdir = readdir(sd)))
			if (sdir->d_name[0] != '.' || ls->f.fa == 1)
			{
				ft_memset((char *)path, 0, 1025) ? ft_strcpy(path, name) &&
				ft_strcat(path, "/") && ft_strcat(path, sdir->d_name) : 0;
				node = t_new_node(path, sdir->d_name);
				if (lstat(path, &node->buf) != -1)
				{
					get_meta(ls, node);
					r = ls->insert(ls, r, node);
				}
			}
	sd ? closedir(sd) : 0;
	return (r);
}

t_queue		*inorder_traverse(t_ls *ls, t_tree *r, t_queue *q)
{
	if (!r)
		return (q);
	inorder_traverse(ls, r->left, q);
	if (S_ISDIR(r->buf.st_mode) && ft_strcmp(r->name, ".")
		&& ft_strcmp(r->name, ".."))
	{
		ls->printfn(ls, r);
		if (q)
			enqueue(q, r);
		inorder_traverse(ls, r->right, q);
		if (q)
		{
			r->right = NULL;
			r->left = NULL;
		}
		else
			deallocat_tnode(r);
	}
	else
	{
		ls->printfn(ls, r);
		inorder_traverse(ls, r->right, q);
		deallocat_tnode(r);
	}
	return (q);
}

void		ft_ls(t_ls *ls, t_tree *r)
{
	t_queue	*q;

	if (!r)
		return ;
	ft_ls(ls, r->left);
	if ((access(r->path, X_OK) == 0) &&
		(access(r->path, R_OK) == 0) && S_ISDIR(r->buf.st_mode))
	{
		ls->fnptr_dir_name(ls, r->path);
		q = inorder_traverse(ls, ls_dir(ls, r->path),
			(ls->fnptr_total(ls->total)) && ls->f.fR ? init() : 0);
		if (q)
		{
			while (!is_empty(q))
				ft_ls(ls, dequeue(q));
			free(q);
		}
	}
	else if (((access(r->path, X_OK) != 0) ||
		(access(r->path, R_OK) != 0)) && S_ISDIR(r->buf.st_mode))
		ft_printf("ft_ls: %s: Permission denied", r->name);
	else
		ls->printfn(ls, r);
	ft_ls(ls, r->right);
	deallocat_tnode(r);
}
