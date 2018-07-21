/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:22:12 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/21 16:12:48 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_flags(t_ls *ls, char *s, t_flags *f)
{
	char *command = "1lRart";
	uint8_t i;

	i = -1;
	while (s[++i])
	{
		if (!ft_strcchr(command, s[i]))
			invalide_cmd();
		//if (twidth < 2 * ncol)
		f->fa = !f->fa && CE_('a', s[i]) ? 1 : f->fa;
		if(!f->fR && (f->fR = CE_('R', s[i])))
			;//ls->is_recursive = ft_ls;
		if (!f->ft && (f->ft = CE_('t', s[i])))
			ls->compare = compare_by_time;
		if (!f->fr && (f->fr = CE_('r', s[i])) && !f->ft)
			ls->compare = compare_reverse_name;
		if (!f->fl && (f->fl = CE_('l', s[i])))
			ls->printfn = print_long_format;
	}
}

t_tree	*ls_dir(t_ls *ls, char *name)
{
	static char 	path[1025];
	DIR				*sd;
	struct dirent	*sdir;
	t_tree			*node;
	t_tree			*r;

	r = NULL;
	if ((sd = opendir(name)))
	{
		while ((sdir = readdir(sd)) != NULL)
		{
			if (sdir->d_name[0] != '.')
			{
				ft_memset((char *)path, 0, 1025);
				ft_strcpy(path, name);
				ft_strcat(path, "/");
				ft_strcat(path, sdir->d_name);
				//ft_printf("%s\n", path);
				node = t_new_node(path, sdir->d_name);
				lstat(path, &node->buf);
				get_meta(ls, node);
				ls->q && S_ISDIR(node->buf.st_mode) && ft_printf("hello queue\n") ? enqueue(ls->q, node) : 0;
				r = insert_by_flags(ls, r, node);
			}
		}
		closedir(sd);
	}
	return (r);
}

void ft_ls(t_ls *ls, t_tree *r)
{
    if (!r)
		return ;
	ft_ls(ls, r->left);
    ls->printfn(ls, r);
	ft_ls(ls, r->right);
}

t_queue *queue_subdir(t_ls *ls, t_queue *q)
{
	t_tree		*r;

	// if(!q)
	// 	return(NULL);
	r = NULL;
	while(!is_empty(q))
	{
		r = insert_by_flags(ls, r, (t_tree *)dequeue(q));
	}
	inorder_traverse(ls, r);
	free((t_queue *)q);
	q = NULL;
	return(q);

}

void	inorder_traverse(t_ls *ls, t_tree *r)
{
	if (!r)
		return ;
	inorder_traverse(ls, r->left);
	if (S_ISDIR(r->buf.st_mode))
	{
		ls->f.fR && !ls->q ? ls->q = init() : 0;
		//if(ls->num_arg > 1)
		ft_printf("%s:\n", r->path);
		ft_ls(ls, ls_dir(ls, r->path));
		if (ls->q && !is_empty(ls->q))
		{
			ls->q = queue_subdir(ls, ls->q);
		}
	}
	else
		ls->printfn(ls, r);
	inorder_traverse(ls, r->right);
	free(r->name);
	free(r->path);
	free(r);
}

/*
**check the arguments and put the bad args in
**b_args three for inorder sorting;
**and the good args in r tree also for sorting
**according to the flags;
**after the two operation the bad flags are printed;
*/

void	parse_argv(t_ls *ls, char *s)
{
	t_tree				*node;

	
	if (s[0] == '-' && !ls->f.isarg)
		parse_flags(ls, ++s, &ls->f);
	else if ((s && s[0] != '-' && (ls->f.isarg = 1)) || (s && ls->f.isarg == 1))
	{
		ls->num_arg++;
		node = t_new_node(s, s);
		if (lstat(node->path, &node->buf) != 0)
			ls->b_args = insert_by_name(ls->b_args, node);
		else
			ls->r = insert_by_flags(ls, ls->r, node);
	}
}
