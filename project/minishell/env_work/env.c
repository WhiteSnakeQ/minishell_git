/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:08:01 by abobylev          #+#    #+#             */
/*   Updated: 2024/01/09 11:29:25 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**make_env_str(t_env *env)
{
	t_env		*help;
	t_helper	hp;
	char		**envs;

	hp.i = 0;
	hp.j = 0;
	help = env;
	while (help && hp.j++ > -1)
		help = help->next;
	envs = malloc(sizeof(char *) * (hp.j + 1));
	if (!envs)
		exit(print_error(MALCERR));
	help = env;
	while (hp.j > hp.i)
	{
		envs[hp.i++] = create_one_env(help);
		if (!envs[hp.i - 1])
		{
			hp.i--;
			hp.j--;
		}
		help = help->next;
	}
	envs[hp.i] = NULL;
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

static t_env	*remove_env(t_env *env, char *key, int size)
{
	t_hlp	hlp;

	hlp.first = env;
	hlp.prev = NULL;
	while (env)
	{
		hlp.next = env->next;
		if (ft_strcmp(env->key, key) == 0)
		{
			free_string(env->key);
			free_string(env->value);
			free(env);
			env = NULL;
			if (size >= 1 && hlp.first)
			{
				hlp.prev->next = hlp.next;
				return (hlp.first);
			}
			else
				return (hlp.next);
		}
		hlp.prev = env;
		env = env->next;
	}
	return (NULL);
}

void	env_remove_key(t_prj *prj, char *key)
{
	t_env	*env;
	int		size;

	if (!key)
		return ;
	if (!prj->env)
		return ;
	if (!prj->env->next)
		size = 0;
	else
		size = 1;
	env = remove_env(prj->env, key, size);
	prj->env = env;
}

int	env_change_key(t_prj *prj, char *key, char *new_val)
{
	t_env	*env;
	int		finish;

	if (!key)
		return (0);
	env = prj->env;
	finish = 0;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if ((new_val && !env->value) || (new_val && env->value))
			{
				free_string(env->value);
				env->value = ft_strdup(new_val, 0);
			}
			finish++;
		}
		env = env->next;
	}
	if (finish == 1)
		return (free_strings(prj->env_str), \
			prj->env_str = make_env_str(prj->env), finish);
	return (finish);
}
