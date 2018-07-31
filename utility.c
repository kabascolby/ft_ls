/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 09:35:45 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 21:24:34 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_winsize(t_ls *ls)
{
	struct winsize win;

	ioctl(0, TIOCGWINSZ, &win);
	if (0 >= (ls->twidth = win.ws_col))
		ls->twidth = 80;
	ls->theight = win.ws_row;
}

void	get_meta(t_ls *ls, t_tree *n)
{
	ls->pwuser = NULL;
	ls->grpnam = NULL;
	if (getpwuid(n->buf.st_uid))
	{
		ls->pwuser = getpwuid(n->buf.st_uid);
		ft_memset((char *)n->un, 0, 1025);
		ft_strcpy(n->un, ls->pwuser->pw_name);
	}
	if (getgrgid(n->buf.st_gid))
	{
		ls->grpnam = getgrgid(n->buf.st_gid);
		ft_memset((char *)n->gn, 0, 1025);
		ft_strcpy(n->gn, ls->grpnam->gr_name);
	}
	ls->total += n->buf.st_blocks;
	EXPC(ls->inode_max, ft_numdigit(n->buf.st_ino));
	EXPC(ls->size_max, ft_numdigit(n->buf.st_blocks));
	EXPC(ls->szmax, ft_numdigit(n->buf.st_size));
	EXPC(ls->lnmax, ft_numdigit(n->buf.st_nlink));
	EXPC(ls->uidmax, ft_numdigit((int)n->buf.st_uid));
	EXPC(ls->gidmax, ft_numdigit((int)n->buf.st_gid));
	EXPC(ls->nmax, ft_strlen(n->name) + 1);
	EXPC(ls->unmax, ft_strlen(n->un) + 1);
	EXPC(ls->gnmax, ft_strlen(n->gn) + 1);
}

/*
**"ft" is the file time
**"today"s is the current local time
**mmm dd  yyyy "%e %b  %Y "|| dd mmm  yyyy
**mmm dd hh:mm "%e %b %R "|| dd mmm hh:mm
*/

char	*display_time(time_t ft)
{
	time_t			today;
	static char		times[80];
	char			*format;

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
	static char	num[100];
	uint16_t	space;

	space = 0;
	ft_memset((char *)num, 0, 100);
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
	{
		if (minor(buf.st_rdev) > 255 || minor(buf.st_rdev) < 0)
			ft_printf("%3d, 0x%08x ", major(buf.st_rdev),
				(u_int)minor(buf.st_rdev));
		else
			(void)ft_printf("%3d, %3d ",
				major(buf.st_rdev), minor(buf.st_rdev));
		ls->minormax = 8;
	}
	else
		(void)ft_printf(" %*lld", ls->minormax + ls->szmax, buf.st_size);
	return ("");
}

char	*chmod_format(t_tree *node, unsigned short n)
{
	static char	f[10];
	char		link[1025];

	ft_memset((char *)f, 0, 10) ? ft_memset((char *)link, 0, 1025) : 0;
	f[0] = ((n & S_IFMT) == S_IFBLK) ? 'b' : f[0];
	f[0] = ((n & S_IFMT) == S_IFCHR) ? 'c' : f[0];
	f[0] = ((n & S_IFMT) == S_IFDIR) ? 'd' : f[0];
	f[0] = ((n & S_IFMT) == S_IFIFO) ? 'p' : f[0];
	if (SYMLINK && (readlink(node->path, link, sizeof(link) - 1)) == -1)
		ft_putendl("error");
	SYMLINK ? NAMECAT(&node->name, ft_strlen(node->name) + 1, " -> ") : 0;
	SYMLINK ? NAMECAT(&node->name, ft_strlen(node->name) + 1, link) : 0;
	f[0] = ((n & S_IFMT) == S_IFREG) ? '-' : f[0];
	f[0] = ((n & S_IFMT) == S_IFSOCK) ? 's' : f[0];
	f[1] = (n & S_IRUSR) ? 'r' : '-';
	f[2] = (n & S_IWUSR) ? 'w' : '-';
	f[3] = (n & S_IXUSR) ? 'x' : '-';
	f[4] = (n & S_IRGRP) ? 'r' : '-';
	f[5] = (n & S_IWGRP) ? 'w' : '-';
	f[6] = (n & S_IXGRP) ? 'x' : '-';
	f[7] = (n & S_IROTH) ? 'r' : '-';
	f[8] = (n & S_IWOTH) ? 'w' : '-';
	f[9] = (n & S_IXOTH) ? 'x' : '-';
	return (f);
}
