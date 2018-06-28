/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:36:22 by lkaba             #+#    #+#             */
/*   Updated: 2018/06/24 07:21:30 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void invalide_cmd(void)
{
	ft_putendl("Invalide commande\n usage:\
		ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]");
	exit(1);
}