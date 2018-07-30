/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 12:35:41 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 14:15:34 by lkaba            ###   ########.fr       */
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
	ft_printf("%*d ",ls->inode_max, n);
}

void	print_usrid(t_ls *ls, uint32_t n)
{
	ft_printf(" %*d ",ls->uidmax + 1, n);
}

void	print_grpid(t_ls *ls, uint32_t n)
{
	ft_printf("%*d ",ls->gidmax + 1, n);
}

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
	ft_printf("%*s ",ls->gnmax, s);
}

void	print_user_name(t_ls *ls, char *s)
{
	ft_printf(" %-*s",ls->unmax, s);
}

void	print_dirname(t_ls *ls, char *s)
{
	(void)ls;
	ft_printf("\n%s:\n", s);
}

void	no_print_string(t_ls *ls, char *s)
{
	(void)s;
	(void)ls;
}

void	no_print_dirname(t_ls *ls, char *s)
{
	(void)s;
	ls->fnptr_dir_name = print_dirname;
}

char	*chmod_format(t_tree *node, unsigned short n)
{
	// if(n == 0)
	// 	ft_putstr("hskjkjskgjskgksvhskgskhjsgk\n");
	static char f[10];
	char link[1025];

	ft_memset((char *)f, 0, 10);
	f[0] = ((n & S_IFMT) == S_IFBLK) ? 'b': f[0];
	f[0] = ((n & S_IFMT) == S_IFCHR) ? 'c': f[0];
	f[0] = ((n & S_IFMT) == S_IFDIR) ? 'd': f[0];
	f[0] = ((n & S_IFMT) == S_IFIFO) ? 'p': f[0];
	if ((n & S_IFMT) == S_IFLNK && (f[0] = 'l'))
	{
		ft_memset((char *)link, 0, 1025);
		if ((readlink(node->path, link, sizeof(link) - 1)) == -1)
			ft_putendl("error link");
		 node->name = ft_str_cat_free(&node->name, ft_strlen(node->name) + 1, " -> ");
		 node->name = ft_str_cat_free(&node->name, ft_strlen(node->name) + 1, link);
	}
	f[0] = ((n & S_IFMT) == S_IFREG) ? '-': f[0];
	f[0] = ((n & S_IFMT) == S_IFSOCK) ? 's': f[0];
	ft_strcat(f, (n & S_IRUSR) ? "r" : "-");
	ft_strcat(f, (n & S_IWUSR) ? "w" : "-");
	ft_strcat(f, (n & S_IXUSR) ? "x" : "-");
	ft_strcat(f, (n & S_IRGRP) ? "r" : "-");
	ft_strcat(f, (n & S_IWGRP) ? "w" : "-");
	ft_strcat(f, (n & S_IXGRP) ? "x" : "-");
	ft_strcat(f, (n & S_IROTH) ? "r" : "-");
	ft_strcat(f, (n & S_IWOTH) ? "w" : "-");
	ft_strcat(f, (n & S_IXOTH) ? "x" : "-");
	return (f);
}