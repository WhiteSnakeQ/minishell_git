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

void    echo(char **strs, t_prj *prj)
{
    int nl;
    int i;

    (void)prj;
    nl = 1;
    i = 1;
    if (strs[1] && ft_strcmp(strs[1], "-n") == 0)
    {
        nl = 0;
        i++;
    }
    while (strs[i])
        ft_printf(1, strs[i++]);
    if (nl == 1)
        ft_printf(1, "\n");
    // exit(0); later
}