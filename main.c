/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 07:56:37 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 21:31:00 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	int32_t	i;
	t_ls	ls;

	ft_bzero(&ls, sizeof(t_ls));
	ls.fnptr_total = no_print_total;
	ls.compare = compare_by_name;
	ls.printfn = print_multi_col;
	ls.insert = insert_by_flags;
	ls.fnptr_user_name = print_user_name;
	ls.inode_print = noprint;
	ls.size_print = noprint;
	ls.fnptr_grp_name = print_grp_name;
	ls.fnptr_user_id = noprint;
	ls.fnptr_grp_id = noprint;
	ls.is_recursive = NULL;
	if (argc < 1 || ft_strnequ(argv[0], "ft_ls", 5))
		invalide_cmd();
	i = 0;
	while (++i < argc)
		parse_argv(&ls, argv[i]);
	ls.fnptr_dir_name = ls.num_arg > 1 ? print_dirname : no_print_dirname;
	if (!ls.f.isarg)
		parse_argv(&ls, ".");
	inorder_print(ls.b_args, "ft_ls: ", ": No such file or directory");
	get_winsize(&ls);
	ft_ls(&ls, ls.r);
	return (0);
}
