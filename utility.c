/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 09:35:45 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/18 05:14:04 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//this have to change according to -R
//because s will change and take the full path
uint8_t compare_by_time(t_tree *a, t_tree *b)
{
	if(a->buf.st_mtimespec.tv_sec < b->buf.st_mtimespec.tv_sec)
		return(1);
	else if (a->buf.st_mtimespec.tv_sec == b->buf.st_mtimespec.tv_sec)
	{
		if(a->buf.st_mtimespec.tv_nsec < b->buf.st_mtimespec.tv_nsec)
			return (1);
	}
	return (0);
}

uint8_t compare_by_name(t_tree *a, t_tree *b)
{
	return(ft_strcmp(a->name, b->name) > 0 ? 1 : 0);
}

uint8_t compare_reverse_name(t_tree *a, t_tree *b)
{
	return(ft_strcmp(a->name, b->name) > 0 ? 0 : 1);
}


void get_winsize(t_ls *ls)
{
	struct winsize win;
	ioctl(0, TIOCGWINSZ, &win);
	if(0 >= (ls->twidth = win.ws_col))
		ls->twidth = 80;
	ls->theight = win.ws_row;
	//printf("Screen width: %i  Screen height: %i\n", win.ws_col, win.ws_row);
}

void get_meta(t_ls *ls, t_tree *n)
{
	uint8_t cpt;
	long long num;

	ls->pwuser = NULL;
	ls->grpnam = NULL;
	num = n->buf.st_size;
	cpt = 0;
	while (num != 0)
	{
		num /= 10;
		cpt++;
	}
	ls->pwuser = getpwuid(n->buf.st_uid);
	ls->grpnam = getgrgid(n->buf.st_gid);
	ft_memset((char *)n->un, 0, 1025);
	ft_memset((char *)n->gn, 0, 1025);
	ft_strcpy(n->un, ls->pwuser->pw_name);
	ft_strcpy(n->gn, ls->grpnam->gr_name);
	ls->total += n->buf.st_size;
	EXPC(ls->szmax, cpt);
	EXPC(ls->nmax, ft_strlen(n->name) + 1);
	EXPC(ls->unmax, ft_strlen(n->un) + 1);
	EXPC(ls->gnmax, ft_strlen(n->gn) + 1);
}

char *chmod_format(t_tree *node, unsigned short n)
{
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

////////////// printing Handler
void	print_multi_col(t_ls *ls, t_tree *node)
{
	// ls->ncol = ls->twidth / ls->nmax;
	// if (ls->twidth < 2 * ls->ncol)
	ls->ncol = 0;
	ft_printf("%s\n", node->name);
	//ft_printf("%*s", node->name);
}

void	print_simple(t_ls *ls, t_tree *node)
{
	ft_printf("%s\n", node->name, ls->gnmax);
}

/*
**"ft" is the file time
**"today"s is the current local time
**mmm dd  yyyy "%e %b  %Y "|| dd mmm  yyyy
**mmm dd hh:mm "%e %b %R "|| dd mmm hh:mm
**
*/

char	*display_time(time_t ft)
{
	time_t			today;
	static char 	times[80];
	char			*format;
	
	today = 0;
	today = time(NULL);
	if (ft + SIXMONTH > today && ft <= today)
			format = "%b %e %R ";
	else if (today + SIXMONTH < ft && today < ft)
		format = "%b %e %Y ";
	else
		format = "%b %e %Y ";
	strftime(times, sizeof(times), format, localtime(&ft));
	return (times);
}

char	*minor_major_size(t_ls *ls, struct stat buf)
{
	static char num[100];
	uint16_t		space;
	
	space = 0;
	ft_memset((char *)num, 0, 100);
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
	{
		if (minor(buf.st_rdev) > 255 || minor(buf.st_rdev) < 0)
		{
			(void)ft_printf("%3d, 0x%08x ",
				major(buf.st_rdev),
				(u_int)minor(buf.st_rdev));
		}
		else
			(void)ft_printf("%3d, %3d ",
				major(buf.st_rdev), minor(buf.st_rdev));
		ls->minormax = 8;
	}
	else
		(void)ft_printf("%*lld", ls->minormax + ls->szmax, buf.st_size);
	return("");
}

void	print_long_format(t_ls *ls, t_tree *node)
{
	char    *f;
	uint8_t ln;
	char 	*times;
	long long  size;
	f = chmod_format(node, node->buf.st_mode);
	ln = node->buf.st_nlink;
	size = node->buf.st_size;
	times = display_time(node->buf.st_mtimespec.tv_sec);
	ft_printf("%s %2d %-*s %-*s", f, ln, ls->unmax, node->un, ls->gnmax, node->gn);
	minor_major_size(ls, node->buf);
	ft_printf(" %.12s %s\n", times, node->name);
}



// int
// sizecmp(a, b)
// 	const FTSENT *a, *b;
// {
// 	if (b->fts_statp->st_size > a->fts_statp->st_size)
// 		return (1);
// 	if (b->fts_statp->st_size < a->fts_statp->st_size)
// 		return (-1);
// 	else
// 		return (namecmp(a, b));
// }

// int
// revsizecmp(a, b)
// 	const FTSENT *a, *b;
// {
// 	if (b->fts_statp->st_size > a->fts_statp->st_size)
// 		return (-1);
// 	if (b->fts_statp->st_size < a->fts_statp->st_size)
// 		return (1);
// 	else
// 		return (revnamecmp(a, b));
// }

// birthcmp(const FTSENT *a, const FTSENT *b)
// {
// 	if (b->fts_statp->st_birthtime > a->fts_statp->st_birthtime)
// 		return (1);
// 	else if (b->fts_statp->st_birthtime < a->fts_statp->st_birthtime)
// 		return (-1);
// 	else if (BTIMENSEC_CMP(b->fts_statp, >, a->fts_statp))
// 		return (1);
// 	else if (BTIMENSEC_CMP(b->fts_statp, <, a->fts_statp))
// 		return (-1);
// 	else
// 		return (namecmp(a, b));
// }

// int
// revbirthcmp(const FTSENT *a, const FTSENT *b)
// {
// 	if (b->fts_statp->st_birthtime > a->fts_statp->st_birthtime)
// 		return (-1);
// 	else if (b->fts_statp->st_birthtime < a->fts_statp->st_birthtime)
// 		return (1);
// 	else if (BTIMENSEC_CMP(b->fts_statp, >, a->fts_statp))
// 		return (-1);
// 	else if (BTIMENSEC_CMP(b->fts_statp, <, a->fts_statp))
// 		return (1);
// 	else
// 		return (revnamecmp(a, b));
// }