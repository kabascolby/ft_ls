/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 13:15:00 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 21:23:58 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <stdint.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
# define EXPC(a, b) ((a) = (a) < (b) ? (b) : (a))
# define SIXMONTH ((365 / 2) * 86400)
# define NOPRINT(a) (void)0
# define FSTR "acglnuiRrst"
# define SYMLINK ((n & S_IFMT) == S_IFLNK && (f[0] = 'l'))
# define NAMECAT node->name = ft_str_cat_free
typedef struct			s_flags
{
	uint8_t			f1:1;
	uint8_t			fl:1;
	uint8_t			fR:1;
	uint8_t			fa:1;
	uint8_t			fr:1;
	uint8_t			ft:1;
	uint8_t			fc:1;
	uint8_t			fu:1;
	uint8_t			fi:1;
	uint8_t			fs:1;
	uint8_t			fg:1;
	uint8_t			fn:1;
	uint8_t			isarg:1;

}						t_flags;

typedef struct			s_tree
{
	char			*name;
	char			*path;
	struct stat		buf;
	char    		un[1025];
	char    		gn[1025];
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

/*
**r is the root of the tree
**f is a copy of my flag struct
**dq is my deque data structure;
**nmax is name max;
*/

typedef	struct			s_ls
{
	t_flags				f;
	DIR					*d;
	struct dirent		*sd;
	t_tree				*b_args;
	t_tree				*r;
	t_tree				*r2;
	t_tree				*r3;
	t_tree				*fd;
	t_tree				*dir;
	struct passwd 		*pwuser;
	struct group 		*grpnam;
	struct stat			st;
	char				dir_path[1024];
	uint8_t				(*compare)(t_tree *, t_tree *);
	void				(*printfn)(struct s_ls *t_ls, t_tree *node);
	void				(*is_recursive)(struct s_ls *t_ls, t_tree *r);
	t_tree				*(*insert)(struct s_ls *, t_tree *, t_tree *);
	void				(*fnptr_dir_name)(struct s_ls  *, char *);
	void				(*fnptr_user_name)(struct s_ls  *, char *);
	void				(*fnptr_grp_name)(struct s_ls  *, char *);
	int					(*fnptr_total)(uint32_t n);
	void				(*fnptr_user_id)(struct s_ls *, uint32_t n);
	void				(*fnptr_grp_id)(struct s_ls *, uint32_t n);
	void				(*inode_print)(struct s_ls *, uint32_t n);
	void				(*size_print)(struct s_ls *, uint32_t n);
	uint32_t			num_arg;
	uint16_t			nmax;
	uint16_t			unmax;
	uint16_t			gnmax;
	uint16_t			size_max; // calculate
	uint8_t				szmax;
	uint8_t				lnmax;
	uint8_t				inode_max;
	uint8_t				minormax;
	uint8_t				gidmax;
	uint8_t				uidmax;
	uint8_t				ncol;
	uint64_t			total;
	t_queue				*q;
	t_queue				*q2;
	stack_t				stk;
	uint16_t			twidth;
	uint16_t			theight;
}						t_ls;

/*
**Compare fuctions pointed by function pointer
*/

uint8_t		compare_by_time(t_tree *a, t_tree *b);
uint8_t		compare_by_name(t_tree *a, t_tree *b);
uint8_t 	compare_by_status_time(t_tree *a, t_tree *b);
uint8_t		compare_by_access_time(t_tree *a, t_tree *b);

/*
** Print function
*/

int		print_total(uint32_t n);
int		no_print_total(uint32_t n);
void	print_simple(t_ls *ls, t_tree *node);
void	print_multi_col(t_ls *ls, t_tree *node);
void	print_long_format(t_ls *ls, t_tree *node);
char	*chmod_format(t_tree *node, unsigned short n);
void	noprint(t_ls *, uint32_t n);
void 	print_inode(t_ls *, uint32_t n);
void	print_grp_name(t_ls *ls, char *s);
void	print_user_name(t_ls *ls, char *s);
void 	print_sizeblk(t_ls *, uint32_t n);
void	no_print_string(t_ls *ls, char *s);
void	print_usrid(t_ls *ls, uint32_t n);
void	print_grpid(t_ls *ls, uint32_t n);

/*
**Print utility
*/

void	get_winsize(t_ls *ls);
void	get_meta(t_ls *ls, t_tree *n);
char	*display_time(time_t ft);


void	invalide_cmd(void);
void	parse_argv(t_ls *ls, char *s);
void	parse_flags(t_ls *ls, char *s, t_flags *f);
void	parse_flags2(t_ls *ls, char *s, t_flags *f);
void	display_arg(t_ls *ls, t_tree *r, t_tree *t);
char	*minor_major_size(t_ls *ls, struct stat buf);

void simple_ls(t_ls *ls, t_tree *r);
t_tree	*insert_tree(t_tree *r, char *s);
t_tree	*insert_tree_rev(t_tree *r, char *s);

t_tree	*t_new_node(char *path, char *name);
t_tree	*insert_by_name(t_tree *r, t_tree *node);
t_tree	*insert_by_flags(t_ls *ls, t_tree *r, t_tree *node);
t_tree	*insert_reverse_flags(t_ls *ls, t_tree *r, t_tree *node);
void	inorder_print(t_tree *r, char *info1, char *info2);
void	inorder_print2(t_ls *ls, t_tree *r);
void	recursive_ls(t_ls *ls, void *);
void	ls_print(t_ls *ls);
void	deallocat_tnode(t_tree *r);
void	ft_ls(t_ls *ls, t_tree *r);
void	print_dirname(t_ls *ls, char *s);
void	no_print_dirname(t_ls *ls, char *s);
#endif
