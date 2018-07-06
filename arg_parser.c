/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:22:12 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/04 23:30:52 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_flags(t_ls *ls, char *s, t_flags *f)
{
	ft_putstr("here\n");
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

void	parse_directory(char *s, t_ls *ls)
{
	struct dirent *sd;
	//printf("string = %s | value of directory flags %hhu", s, ls->f.isdir);
	//printf("imhere\n");
	//printf("fl = %hhu\n | fR = %hhu\n | fa = %hhu\n | fr = %hhu\n | ft = %hhu\n",ls->f.fl ,ls->f.fR ,ls->f.fa ,ls->f.fr ,ls->f.ft);
	ls->d = opendir(s);
	if (ls->d == NULL)
		printf("empty folder\n");
	while ((sd = readdir(ls->d)))
		ls->r = ls->insert_func(ls->r, sd->d_name);
	//traverse_dir(ls);
	inorder_print(ls->r);
	closedir(ls->d);
}

t_tree	*create_node(t_tree *tmp, char *s)
{
	tmp = (t_tree *)malloc(sizeof(t_tree));
	tmp->data = s;
	tmp->left = NULL;
	tmp->right = NULL;
	return(tmp);
}

void	parse_args(char *s, t_ls *ls)
{
	if (s && s[0] != '-' && (ls->f.isdir = 1))
		parse_directory(s, ls);
	else if (s[0] == '-' && !ls->f.isdir)
		parse_flags(ls, ++s, &ls->f);
}
