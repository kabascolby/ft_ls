/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 07:56:37 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/09 08:16:07 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	int32_t i;
	t_ls ls;

	ft_bzero(&ls, sizeof(t_ls));
	ls.compare = compare_by_name;
	//ls.dq = init_deque(30, sizeof(char *));
	if (argc < 1 || ft_strnequ(argv[0], "ft_ls", 5))
		invalide_cmd();
	i = 0;
	while (++i <  argc)
		parse_argv(&ls, argv[i]);
	ls_print(&ls);
	//i = -1;
	/* while(++i < ls.av.curr_size)
		ft_printf("%s\n", (char *)ls.av.tab + i * 8); */
	// !ls.f.isarg ? display_arg(&ls, ".") : validate_validate;
}