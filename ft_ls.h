/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 13:15:00 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/10 08:06:53 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <stdint.h>
# include <time.h>

// bitfield operator for flags struct


typedef struct			s_flags
{
	u_int8_t			fl:1;
	u_int8_t			fR:1;
	u_int8_t			fa:1;
	u_int8_t			fr:1;
	u_int8_t			ft:1;
	u_int8_t			isarg:1;

}						t_flags;

typedef struct			s_tree
{
	char			*name;
	char			*path;
	struct stat		buf;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*sub_dir;
}					t_tree;

/*
**r is the root of the tree
**f is a copy of my flag struct
**dq is my deque data structure;
*/
typedef	struct			s_ls
{
	t_flags				f;
	DIR					*d;
	struct dirent		*sd;
	t_tree				*b_args;
	t_tree				*r;
	t_tree				*fd;
	t_tree				*dir;
	int					(*compare)(t_tree *, t_tree *);
	t_deque				dq;
}						t_ls;


void	invalide_cmd(void);
void	parse_argv(t_ls *ls, char *s);
void	parse_flags(t_ls *ls, char *s, t_flags *f);
void	display_arg(t_ls *ls, t_tree *r);

t_tree	*insert_tree(t_tree *r, char *s);
t_tree	*insert_tree_rev(t_tree *r, char *s);

t_tree	*t_new_node(char *path, char *name);
t_tree	*insert_by_name(t_tree *r, t_tree *node);
t_tree	*insert_by_flags(t_ls *ls, t_tree *r, t_tree *node);
int		compare_by_time(t_tree *a, t_tree *b);
int		compare_by_name(t_tree *a, t_tree *b);
void	inorder_print(t_tree *r, char *info1, char *info2);
void	inorder_print2(t_ls *ls, t_tree *r);

void	ls_print(t_ls *ls);
void	deallocat_tree(t_tree *r);
t_tree	*ft_ls(t_ls *ls, t_tree *tmp);

/* typedef struct {
	FTSENT *list;
	u_int64_t btotal;
	int bcfile;
	int entries;
	int maxlen;
	u_int s_block;
	u_int s_flags;
	u_int s_lattr;
	u_int s_group;
	u_int s_inode;
	u_int s_nlink;
	u_int s_size;
	u_int s_user;
} DISPLAY; */

// typedef struct s_flags
// {
//     /* flags */
//        int f_accesstime;	/* use time of last access */
//        int f_birthtime;		/* use time of file birth */
//        int f_flags;		/* show flags associated with a file */
//        int f_humanval;		/* show human-readable file sizes */
//        int f_inode;		/* print inode */
// static int f_kblocks;		/* print size in kilobytes */
// static int f_listdir;		/* list actual directory, not contents */
// static int f_listdot;		/* list files beginning with . */
//        int f_longform;		/* long listing format */
//        int f_nonprint;		/* show unprintables as ? */
// static int f_nosort;		/* don't sort output */
//        int f_notabs;		/* don't use tab-separated multi-col output */
//        int f_numericonly;	/* don't convert uid/gid to name */
//        int f_octal;		/* show unprintables as \xxx */
//        int f_octal_escape;	/* like f_octal but use C escapes if possible */
// static int f_recursive;		/* ls subdirectories also */
// static int f_reversesort;	/* reverse whatever sort is used */
//        int f_sectime;		/* print the real time for all files */
// static int f_singlecol;		/* use single column output */
//        int f_size;		/* list size in short listing */
//        int f_slash;		/* similar to f_type, but only for dirs */
//        int f_sortacross;	/* sort across rows, not down columns */ 
//        int f_statustime;	/* use time of last mode change */
//        int f_stream;		/* stream the output, separate with commas */
// static int f_timesort;		/* sort by time vice name */
// static int f_sizesort;		/* sort by size */
//        int f_type;		/* add type character for non-regular files */
// static int f_whiteout;		/* show whiteout entries */
//        int f_acl;		/* show ACLs in long listing */
//        int f_xattr;		/* show extended attributes in long listing */
//        int f_group;		/* show group */
//        int f_owner;		/* show owner */
// }                   s_flags;

//enum struct
/* enum					e_l
{
	H = 1,
	HH,
	L,
	LL,
	J,
	Z
}; */

#endif
