/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 09:35:45 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/07 11:22:32 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ls.h"

//this have to change according to -R
//because s will change and take the full path
int compare_flags(t_ls *ls, char * s)
{

    if(!ls->f.ft)
    {
        if(ft_strcmp(ls->r->data, s) > 0 && !ls->f.fr)
            return(1);
        else
            return(-1);
    }
    else(ft_strcmp(ls->r->buf.st_mtime, ))
}