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
        prj->exit = 1;
        return ;
    }
    prj->exit = 0;
    env_remove_key(prj, str);
}

static void    add_puth(t_prj *prj)
{
    int		i;

	i = 0;
	while (prj->env_str[i])
	{
		if (ft_strncmp("PATH", prj->env_str[i], 4) == 0)
			break ;
		i++;
	}
    if (!prj->env_str[i])
    {
        return ;
    }
	prj->paths = ft_split(&prj->env_str[i][5], ':');
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
        free_strings(prj->paths);
        prj->paths = NULL;
        add_puth(prj);
    }
    return ;
}
