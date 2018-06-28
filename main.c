/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 07:56:37 by lkaba             #+#    #+#             */
/*   Updated: 2018/06/24 12:03:14 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	t_ls ls;
	ft_bzero(&ls, sizeof(t_ls));
	uint8_t i;
	if (argc < 1 || ft_strnequ(argv[0], "ft_ls", 5))
		invalide_cmd();
	i = 0;
	while(++i <  argc)
		parse_args(argv[i], &ls);
	if(!ls.f.isdir)
		parse_directory(".", &ls);
}