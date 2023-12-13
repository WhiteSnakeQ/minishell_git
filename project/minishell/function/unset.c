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

static void    del_one(char *str, t_prj *prj)
{
    if ((str[0] >= '0' && str[0] <= '9') || symbl_in_str(str, '=') == 1)
    {
        ft_printf(2, "minishell: unset: `%s':%s\n", str, NVID);
        return ;
    }
    env_remove_key(prj, str);
}

void    unset(char **strs, t_prj *prj)
{
    int i;

    i = 1;
    while (strs[i])
        del_one(strs[i++], prj);
    if (strs[1])
    {
        free_strings(prj->env_str);
        prj->env_str = make_env_str(prj->env);
    }
    // exit(0);
}
