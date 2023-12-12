/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 12:46:32 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void    cd(char **strs, t_prj *prj)
{
    void *dir;

    if (strs[2])
    {
        ft_printf(2, INVNARG);
        return ;
    }
    dir = opendir(strs[1]);
    if (dir == 0)
    {
        ft_printf(2, "minishell: %s: ", strs[1]);
        perror(NULL);
    }
    else
    {
        closedir(dir);
        free_string(prj->our_path);
        chdir(strs[1]);
        prj->our_path = getcwd(NULL, 1024);
    }
    // exit(0); later
}
