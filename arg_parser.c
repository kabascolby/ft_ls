/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:22:12 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/07 09:56:37 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_flags(t_ls *ls, char *s, t_flags *f)
{
	//ft_putstr("here\n");
	char *command = "lRart";
	uint8_t i;

	i = -1;
	while (s[++i])
	{
		if (!ft_strcchr(command, s[i]))
			invalide_cmd();
		f->fl = !f->fl && CE_('l', s[i]) ? 1 : f->fl;
		f->fR = !f->fR && CE_('R', s[i]) ? 1 : f->fR;
		f->fa = !f->fa && CE_('a', s[i]) ? 1 : f->fa;
		f->fr = !f->fr && CE_('r', s[i]) ? 1 : f->fr;
		f->ft = !f->ft && CE_('t', s[i]) ? 1 : f->ft;
		if (CE_('r', s[i]))
			ls->insert_func = &insert_tree_rev;
	}
}

void	display_arg(t_ls *ls, char *s)
{
	struct dirent *sd;
	printf(" | fl = %hhu\n | fR = %hhu\n | fa = %hhu\n | fr = %hhu\n | ft = %hhu\n",
		ls->f.fl ,ls->f.fR ,ls->f.fa ,ls->f.fr ,ls->f.ft);

	ls->d = opendir(s);
	if (ls->d == NULL)
		printf("empty folder\n");
	while ((sd = readdir(ls->d)))
	{
		ls->inv_file = ls->insert_func(ls->inv_file, sd->d_name);
	}
	inorder_print(ls->inv_file, "", "");
	closedir(ls->d);
}

void	parse_argv(t_ls *ls, char *s)
{
	struct stat			info;

	if (s[0] == '-' && !ls->f.isarg)
		parse_flags(ls, ++s, &ls->f);
	else if ((s && s[0] != '-' && (ls->f.isarg = 1)) || (s && ls->f.isarg == 1))
	{
		if (lstat(s, &info) != 0)
			ls->inv_file = insert_tree(ls->inv_file, s);
		else
			ls->r = insert_tree(ls->r, s);
	}
}

/*
** Print the arguments according to the flags;
** and free all varialble I already printed.
*/

void	ls_print(t_ls *ls)
{
	//uint32_t	i;
	//void		*tmp;

	inorder_print(ls->inv_file, "ft_ls: ", ": No such file or directory");
	deallocat_tree(ls->inv_file);
}

// void argv_check(t_ls *ls, void *tmp)
// {
// 	uint32_t i;
// 	t_tree *r;
// 	r = NULL;
// 	char	**s = tmp;
// 	//struct stat buf;
// 	(void)ls;
// 	i = -1;
// 	while(++i < 4)
// 	{
// 		//lstat(((char *)tmp + i * ls->av.data_size), &buf);
// 		ft_printf("device %s\n", s[i]);
// 		// if (buf.st_dev == 0)
// 		// {
// 		// 	r = insert_tree(r, ((char *)tmp + i * ls->av.data_size));
// 		// }
// 		// else
// 		// {
// 		// 	ls->av.front = 0;
// 		// 	ls->av.rear = 0;
// 		// 	ls->av.curr_size = 0;
// 		// 	enqueue_front(&ls->av, tmp + i * ls->av.data_size);
// 		// }
// 	}
// 	free(tmp);
// }
