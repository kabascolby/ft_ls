/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:22:12 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 19:40:00 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_flags(t_ls *ls, char *s, t_flags *f)
{
	uint8_t	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_strcchr(FSTR, s[i]))
			invalide_cmd();
		f->fa = !f->fa && CE_('a', s[i]) ? 1 : f->fa;
		f->fR = !f->fR ? CE_('R', s[i]) : f->fR;
		if (!f->fc && (f->fc = CE_('c', s[i])))
			f->fu = 0;
		if (!f->ft && (f->ft = CE_('t', s[i])))
			ls->compare = compare_by_time;
		if (!f->fu && (f->fu = CE_('u', s[i])))
			f->fc = 0;
		if (!f->fr && (f->fr = CE_('r', s[i])) && !f->ft)
			ls->insert = insert_reverse_flags;
		if (!f->fl && (f->fl = CE_('l', s[i])))
			ls->printfn = print_long_format;
		if (!f->fi && (f->fi = CE_('i', s[i])))
			ls->inode_print = print_inode;
		if (!f->fs && (f->fs = CE_('s', s[i])))
			ls->size_print = print_sizeblk;
	}
}

void	parse_flags2(t_ls *ls, char *s, t_flags *f)
{
	uint8_t	i;

	i = -1;
	while (s[++i])
	{
		!ft_strcchr(FSTR, s[i]) ? invalide_cmd() : 0;
		if (!f->fg && (f->fg = CE_('g', s[i])))
		{
			ls->printfn = print_long_format;
			ls->fnptr_user_name = no_print_string;
		}
		if (!f->fn && (f->fn = CE_('n', s[i])))
		{
			ls->printfn = print_long_format;
			ls->fnptr_grp_name = no_print_string;
			ls->fnptr_user_name = no_print_string;
			ls->fnptr_user_id = print_usrid;
			ls->fnptr_grp_id = print_grpid;
		}
	}
	ls->fnptr_user_id = (f->fg && f->fn) ? noprint : ls->fnptr_user_id;
	ls->compare = (f->fc && f->ft) ? compare_by_status_time : ls->compare;
	ls->compare = (f->fu && f->ft) ? compare_by_access_time : ls->compare;
	ls->fnptr_total = (f->fl || f->fg || f->fn) ? print_total : ls->fnptr_total;
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
	{
		parse_flags(ls, ++s, &ls->f);
		parse_flags2(ls, s, &ls->f);
	}
	else if ((s && s[0] != '-' && (ls->f.isarg = 1)) || (s && ls->f.isarg == 1))
	{
		ls->num_arg++;
		node = t_new_node(s, s);
		if (lstat(node->path, &node->buf) != 0)
			ls->b_args = insert_by_name(ls->b_args, node);
		else
			ls->r = ls->insert(ls, ls->r, node);
	}
}
