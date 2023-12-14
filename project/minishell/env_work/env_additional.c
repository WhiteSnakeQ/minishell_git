/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_additional.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 07:49:37 by kreys             #+#    #+#             */
/*   Updated: 2023/12/14 07:49:59 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	get_value_env_int(char *key, t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(key, curr->key) == 0)
			return (ft_strlen(curr->value));
		curr = curr->next;
	}
	return (0);
}

char	*get_value_env_str(char *key, t_env *env)
{
	t_env   *curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(key, curr->key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
