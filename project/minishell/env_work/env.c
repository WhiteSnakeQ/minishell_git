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

char	**make_env_str(t_env *env)
{
	t_env	*help;
	char	**envs;
	int		size;
	int		i;

	i = 0;
	size = 0;
	help = env;
	while (help)
	{
		help = help->next;
		size++;
	}
	envs = malloc(sizeof(char *) * (size + 1));
	if (!envs)
		exit(print_error(MALCERR));
	envs[size] = NULL;
	help = env;
	while (size > i)
	{
		envs[i++] = create_one_env(help);
		help = help->next;
	}
	return (envs);
}

void	env_add_last(t_prj *prj, char *str)
{
	t_env	*new;
	t_env	*change;

	new = malloc(sizeof(t_env));
	if (!new)
		clean_prj(GET, NULL);
	new->key = new_str_till(str, '=');
	new->value = new_str_after(str, '=');
	new->next = NULL;
	if (!prj->env)
	{
		prj->env = new;
		return ;
	}
	change = prj->env;
	while (change->next)
		change = change->next;
	change->next = new;
}

static t_env	*remove_env(t_env *env, char *key)
{
    t_env	*prev;
    t_env	*next;
    t_env	*first;

	first = env;
	prev = NULL;
	while (env)
	{
		next = env->next;
        if (ft_strcmp(env->key, key) == 0)
        {
            free_string(env->key);
            free_string(env->value);
            free(env);
			env = NULL;
			if (first)
			{
				prev->next = next;
				return (first);
			}
			else
				return (next);
        }
		prev = env;
		env = env->next;
    }
	return (NULL);
}

void	env_remove_key(t_prj *prj, char *key)
{
	t_env	*env;

	if (!key)
		return ;
	env = remove_env(prj->env, key);
	if (env == NULL)
		return ;
	prj->env = env;
}

void	env_change_key(t_prj *prj, char *key, char *new_val)
{
	t_env	*env;
	int		finish;

	if (!key)
		return ;
	env = prj->env;
	finish = 0;
	while (env)
	{
        if (ft_strcmp(env->key, key) == 0)
        {
			free_string(env->value);
			env->value = ft_strdup(new_val, 0);
			finish++;
        }
		env = env->next;
    }
	if (finish == 1)
	{
		free_strings(prj->env_str);
		prj->env_str = make_env_str(prj->env);
	}
}
