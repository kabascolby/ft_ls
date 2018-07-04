/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:22:12 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/03 13:34:05 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "stdio.h"

void	parse_flags(char *s, t_flags *f)
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
	}
}

void	parse_directory(char *s, t_ls *ls)
{
	struct dirent *sd;
	printf("string = %s | value of directory flags %hhu", s, ls->f.isdir);
	//printf("imhere\n");
	//printf("fl = %hhu\n | fR = %hhu\n | fa = %hhu\n | fr = %hhu\n | ft = %hhu\n",ls->f.fl ,ls->f.fR ,ls->f.fa ,ls->f.fr ,ls->f.ft);
	ls->d = opendir(s);
	if (ls->d == NULL)
		printf("empty folder\n");
	while ((sd = readdir(ls->d)))
		build_tree(ls, sd->d_name);
	closedir(ls->d);
}

t_tree	*create_node(t_tree *tmp, char *s)
{
	tmp = (t_tree *)malloc(sizeof(t_tree));
	tmp->name = s;
	tmp->left = NULL;
	tmp->right = NULL;
	return(tmp);
}

void	parse_args(char *s, t_ls *ls)
{
	if (s && s[0] != '-' && (ls->f.isdir = 1))
		parse_directory(s, ls);
	if (s[0] == '-' && !ls->f.isdir)
		parse_flags(++s, &ls->f);
}
