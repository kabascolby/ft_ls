/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 07:56:37 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/21 16:18:06 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	int32_t i;
	t_ls ls;

	ft_bzero(&ls, sizeof(t_ls));
	ls.compare = compare_by_name;
	ls.printfn = print_multi_col;
	ls.is_recursive = NULL;
	if (argc < 1 || ft_strnequ(argv[0], "ft_ls", 5))
		invalide_cmd();
	i = 0;
	while (++i <  argc)
		parse_argv(&ls, argv[i]);
	if(!ls.f.isarg)
		parse_argv(&ls, ".");
	inorder_print(ls.b_args, "ft_ls: ", ": No such file or directory");
	get_winsize(&ls);
	inorder_traverse(&ls, ls.r);
	while(1);
	//ls_print(&ls);
	return (0);
}