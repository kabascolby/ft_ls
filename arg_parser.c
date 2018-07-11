/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:22:12 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/10 08:24:37 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_flags(t_ls *ls, char *s, t_flags *f)
{
	//ft_putstr("here\n");
	char *command = "lRart";
	uint8_t i;

	i = -1;
	while (s[++i])
	{
		if (!ft_strcchr(command, s[i]))
			invalide_cmd();
		f->fl = !f->fl && CE_('l', s[i]) ? 1 : f->fl;
		f->fR = !f->fR && CE_('R', s[i]) ? 1 : f->fR;
		f->fa = !f->fa && CE_('a', s[i]) ? 1 : f->fa;
		f->fr = !f->fr && CE_('r', s[i]) ? 1 : f->fr;
		f->ft = !f->ft && CE_('t', s[i]) ? 1 : f->ft;
		if (CE_('t', s[i]))
			ls->compare = compare_by_time;
	}
}

void	display_arg(t_ls *ls, t_tree *r)
{
	// printf(" | fl = %hhu\n | fR = %hhu\n | fa = %hhu\n | fr = %hhu\n | ft = %hhu\n",
	// 	ls->f.fl ,ls->f.fR ,ls->f.fa ,ls->f.fr ,ls->f.ft);
	if(!r)
		return;
	inorder_print2(ls, r);
			ft_printf("ici\n");
		//ls->dir = ((t_tree *)dequeue_front(&ls->dq));
		//display_arg(ls, ls->dir);
		ft_putstr("\n");
}

/*
** check the arguments and put the bad args in
** b_args three for inorder sorting;
** and the good args in r tree also for sorting
** according to the flags;
** after the two operation the bad flags are printed;
*/

void	parse_argv(t_ls *ls, char *s)
{
	t_tree				*node;

	if (s[0] == '-' && !ls->f.isarg)
		parse_flags(ls, ++s, &ls->f);
	else if ((s && s[0] != '-' && (ls->f.isarg = 1)) || (s && ls->f.isarg == 1))
	{
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
	display_arg(ls, ls->r);
}

t_tree	*ft_ls(t_ls *ls, t_tree *tmp)
{
	t_tree			*node;
	static char 	path[1024];
	
	while ((ls->sd = readdir(ls->d)))
	{
		if(ls->sd->d_name[0] != '.')
		{
			//ft_putstr(ls->sd->d_name);
			ft_strcpy(path, tmp->path);
			ft_strcat(path, "/");
			ft_strcat(path, ls->sd->d_name);
			// ft_putstr(path);
			// ft_putstr("\n");
			node = t_new_node(path, ls->sd->d_name);
			node = insert_by_flags(ls, tmp->sub_dir, node);
			//node->path = ft_str_cat_free((ft_strdup(node->path)), ft_strlen(tmp->name), "/")
		}
	}
	//inorder_print(ls->b_args, "", "");
	closedir(ls->d);
	return(node);
}