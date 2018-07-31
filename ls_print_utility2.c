/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_utility2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 17:54:39 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 19:46:29 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_sizeblk(t_ls *ls, uint32_t n)
{
	ft_printf("%*d ", ls->size_max, n);
}

void	noprint(t_ls *ls, uint32_t n)
{
	(void)ls;
	(void)n;
}

void	print_grp_name(t_ls *ls, char *s)
{
	ft_printf("%*s ", ls->gnmax, s);
}

void	print_user_name(t_ls *ls, char *s)
{
	ft_printf(" %-*s", ls->unmax, s);
}

void	print_dirname(t_ls *ls, char *s)
{
	(void)ls;
	ft_printf("\n%s:\n", s);
}
