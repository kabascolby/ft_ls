/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_compare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 08:56:29 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/30 19:42:45 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

uint8_t	compare_by_time(t_tree *a, t_tree *b)
{
	if (a->buf.st_mtimespec.tv_sec < b->buf.st_mtimespec.tv_sec)
		return (1);
	else if (a->buf.st_mtimespec.tv_sec == b->buf.st_mtimespec.tv_sec)
	{
		if (a->buf.st_mtimespec.tv_nsec < b->buf.st_mtimespec.tv_nsec)
			return (1);
	}
	return (0);
}

uint8_t	compare_by_name(t_tree *a, t_tree *b)
{
	return (ft_strcmp(a->name, b->name) > 0 ? 1 : 0);
}

uint8_t	compare_by_status_time(t_tree *a, t_tree *b)
{
	if (a->buf.st_ctime < b->buf.st_ctime)
		return (1);
	else if (a->buf.st_ctimespec.tv_sec == b->buf.st_ctimespec.tv_sec)
	{
		if (a->buf.st_ctimespec.tv_nsec < b->buf.st_ctimespec.tv_nsec)
			return (1);
	}
	return (0);
}

uint8_t	compare_by_access_time(t_tree *a, t_tree *b)
{
	if (b->buf.st_atimespec.tv_sec > a->buf.st_atimespec.tv_sec)
		return (1);
	else if (b->buf.st_atimespec.tv_sec < a->buf.st_atimespec.tv_sec)
		return (0);
	return (compare_by_name(a, b));
}
