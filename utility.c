/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 09:35:45 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/09 05:46:32 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ls.h"

//this have to change according to -R
//because s will change and take the full path
int compare_by_time(t_tree *a, t_tree *b)
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

int compare_by_name(t_tree *a, t_tree *b)
{
    return(ft_strcmp(a->name, b->name) > 0 ? 1 : 0);
}