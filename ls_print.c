/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 12:13:12 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 19:48:18 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_multi_col(t_ls *ls, t_tree *node)
{
	ls->ncol = 0;
	ls->inode_print(ls, (int)node->buf.st_ino);
	ls->size_print(ls, (uint32_t)node->buf.st_blocks);
	ft_printf("%s\n", node->name);
}

void	print_simple(t_ls *ls, t_tree *node)
{
	ls->inode_print(ls, (int)node->buf.st_ino);
	ls->size_print(ls, (uint32_t)node->buf.st_blocks);
}

void	print_long_format(t_ls *ls, t_tree *node)
{
	char		*f;
	uint8_t		ln;
	char		*times;
	uint32_t	size;

	f = chmod_format(node, node->buf.st_mode);
	ln = node->buf.st_nlink;
	size = node->buf.st_size;
	times = display_time(node->buf.st_mtimespec.tv_sec);
	ls->inode_print(ls, (int)node->buf.st_ino);
	ls->size_print(ls, (uint32_t)node->buf.st_blocks);
	ft_printf("%s %2d", f, ln);
	ls->fnptr_user_name(ls, node->un);
	ls->fnptr_grp_name(ls, node->gn);
	ls->fnptr_user_id(ls, (int)node->buf.st_uid);
	ls->fnptr_grp_id(ls, (int)node->buf.st_gid);
	minor_major_size(ls, node->buf);
	ft_printf(" %.12s %s\n", times, node->name);
}

void	invalide_cmd(void)
{
	ft_putendl("Invalide commande\n usage:\
		ls [-acglnuiRrst] [file ...]");
	exit(1);
}
