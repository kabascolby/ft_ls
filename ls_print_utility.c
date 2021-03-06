/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 12:35:41 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 19:45:57 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_total(uint32_t n)
{
	ft_printf("total %lld\n", n);
	return (1);
}

int		no_print_total(uint32_t n)
{
	(void)n;
	return (0);
}

void	print_inode(t_ls *ls, uint32_t n)
{
	ft_printf("%*d ", ls->inode_max, n);
}

void	print_usrid(t_ls *ls, uint32_t n)
{
	ft_printf(" %*d ", ls->uidmax + 1, n);
}

void	print_grpid(t_ls *ls, uint32_t n)
{
	ft_printf("%*d ", ls->gidmax + 1, n);
}
