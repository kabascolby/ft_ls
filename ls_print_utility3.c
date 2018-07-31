/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_utility3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 18:25:42 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 19:52:26 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	no_print_string(t_ls *ls, char *s)
{
	(void)s;
	(void)ls;
}

void	no_print_dirname(t_ls *ls, char *s)
{
	(void)s;
	ls->fnptr_dir_name = print_dirname;
}

void	inorder_print(t_tree *r, char *info1, char *info2)
{
	if (!r)
		return ;
	inorder_print(r->left, info1, info2);
	ft_printf("%s%s%s\n", info1, r->name, info2);
	inorder_print(r->right, info1, info2);
	free(r->name);
	free(r->path);
	free(r);
}
