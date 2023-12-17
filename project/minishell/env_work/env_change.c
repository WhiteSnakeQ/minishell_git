/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 07:51:35 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 02:22:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	env_cahnge_key2(t_prj *prj, char *key, char *new_val)
{
	t_env	*env;

	env = prj->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free_string(env->value);
			env->value = ft_strdup(new_val, 0);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
