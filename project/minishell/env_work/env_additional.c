/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_additional.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abobylev <abobylev@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:07:56 by abobylev          #+#    #+#             */
/*   Updated: 2023/12/17 21:08:05 by abobylev         ###   ########.fr       */
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
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(key, curr->key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

char	**export_all(t_env *env, int size)
{
	char	**strs;
	char	*clean;
	int		i;

	i = 0;
	strs = malloc(sizeof(char *) * (size + 1));
	strs[size] = NULL;
	while (env)
	{
		strs[i] = ft_strdup(env->key, 0);
		clean = strs[i];
		if (env->value)
		{
			strs[i] = ft_strjoin(strs[i], "=\"");
			free_string(clean);
			clean = ft_strjoin(strs[i], env->value);
			free_string(strs[i]);
			strs[i] = ft_strjoin(clean, "\"");
			free_string(clean);
		}
		i++;
		env = env->next;
	}
	return (strs);
}

static void	swap(char **digit_one, char **digit_two)
{
	char	*intermidiate;

	intermidiate = *digit_one;
	*digit_one = *digit_two;
	*digit_two = intermidiate;
}

void	ft_sort_params(char **tab, int size)
{
	int		i_o_a;
	int		main_iteration;

	main_iteration = size - 1;
	while (main_iteration >= 1)
	{
		i_o_a = main_iteration - 1;
		while (i_o_a >= 0)
		{
			if (ft_strcmp(*(tab + main_iteration), *(tab + i_o_a)) < 0)
				swap((tab + main_iteration), (tab + i_o_a));
			i_o_a--;
		}
		main_iteration--;
	}
}
