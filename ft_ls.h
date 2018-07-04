/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 13:15:00 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/03 13:21:59 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <stdint.h>

// bitfield operator for flags struct


typedef struct			s_flags
{
	u_int8_t			fl:1;
	u_int8_t			fR:1;
	u_int8_t			fa:1;
	u_int8_t			fr:1;
	u_int8_t			ft:1;
	u_int8_t			isdir:1;

}						t_flags;

typedef struct			s_tree
{
	char			*name;
	uint8_t			cpt;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

/*
**r is the root of the tree
**f is a copy of my flag struct
*/
typedef	struct			s_ls
{
	t_flags				f;
	DIR					*d;
	t_tree				r;
}						t_ls;


void	invalide_cmd(void);
void	parse_directory(char *s, t_ls *ls);
void	parse_flags(char *s, t_flags *f);
void	parse_args(char *s, t_ls *ls);


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
