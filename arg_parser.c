/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:22:12 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/17 07:48:03 by lkaba            ###   ########.fr       */
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
		if((f->fR = CE_('R', s[i])))
			ls->is_recursive = ft_ls;
		if ((f->ft = CE_('t', s[i])))
			ls->compare = compare_by_time;
		if ((f->fr = CE_('r', s[i])) && !f->ft)
			ls->compare = compare_reverse_name;
		if ((f->fr = CE_('l', s[i])))
			ls->printfn = print_long_format;
	}
}

void	ft_ls(t_ls *ls, t_tree *r)
{
	// printf(" | fl = %hhu\n | fR = %hhu\n | fa = %hhu\n | fr = %hhu\n | ft = %hhu\n",
	// 	ls->f.fl ,ls->f.fR ,ls->f.fa ,ls->f.fr ,ls->f.ft);
	if (!r)
		return ;
	ft_ls(ls, r->left);
	if (S_ISDIR(r->buf.st_mode))
	{
		ft_printf("\n%s:\ntotal %d\n", r->path, ls->total/512);
		recursive_ls(ls,  r->path);
	}
	else
		ls->printfn(ls, r);
	ft_ls(ls, r->right);
	free(r->name);
	free(r->path);
	free(r);
}

void	recursive_ls(t_ls *ls, char *name)
{
	t_tree			*node;
	t_tree			*r;
	static char 	path[1025];
	DIR				*sd;
	struct dirent	*sdir;

	r = NULL;
	if ((sd = opendir(name)))
	{
		while ((sdir = readdir(sd)))
			if (sdir->d_name[0] != '.')
			{
				ft_memset((char *)path, 0, 1025);
				ft_strcpy(path, name);
				ft_strcat(path, "/");
				ft_strcat(path, sdir->d_name);
				node = t_new_node(path, sdir->d_name);
				lstat(path, &node->buf);
				get_meta(ls, node);
				//ft_printf("%s", node->gn);
				r = insert_by_flags(ls, r, node);
			}
		closedir(sd);
	}
	ls->is_recursive(ls, r);
}

void simple_ls(t_ls *ls, t_tree *r)
{
	if (!r)
		return ;
	simple_ls(ls, r->left);
	ls->printfn(ls, r);
	simple_ls(ls, r->right);
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
		ls->num_node++;
		node = t_new_node(s, s);
		if (lstat(node->path, &node->buf) != 0)
			ls->b_args = insert_by_name(ls->b_args, node);
		else
			ls->r = insert_by_flags(ls, ls->r, node);
	}
}

void	ls_print(t_ls *ls)
{
	inorder_print(ls->b_args, "ft_ls: ", ": No such file or directory");
	deallocat_tree(ls->b_args);
	ft_ls(ls, ls->r);
	get_winsize(ls);
}