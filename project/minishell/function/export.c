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

static void    add_some_th(char *strs, t_prj *prj)
{
    char    *key;

    if ((strs[0] >= '0' && strs[0] <= '9'))
    {
        ft_printf(2, "minishell: export: `%s':%s\n", strs, NVID);
        return ;
    }
    else
    {
        key = new_str_till(strs, '=');
        env_remove_key(prj, key);
        free_string(key);
        env_add_last(prj, strs);
    }
}

static void    print_exp(t_env *env)
{
    t_env   *curr;

    curr = env;
    while (curr)
    {
        ft_printf(1, curr->key);
        if (curr->value)
            ft_printf(1, "=\"%s\"", curr->value);
        curr = curr->next;
        ft_printf(1, "\n");
    }
}

void    export(char **strs, t_prj *prj)
{
    int i;

    i = 1;
    while (strs[i])
        add_some_th(strs[i++], prj);
    if (!strs[1])
        print_exp(prj->env);
    else
    {
        free_strings(prj->env_str);
        prj->env_str = make_env_str(prj->env);
    }
    // exit(0);
}
