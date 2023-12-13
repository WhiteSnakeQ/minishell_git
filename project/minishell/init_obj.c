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

#include "../headers/minishell.h"

void	make_list_env(char **env, t_prj *prj)
{
	int		i;

	i = 0;
	while (env[i])
		env_add_last(prj, env[i++]);
}

void	took_env(t_prj *prj, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			break ;
		i++;
	}
	prj->paths= ft_split(&env[i][5], ':');
	make_list_env(env, prj);
}

static void	null_struct(t_prj *prj)
{
	prj->list_argv = NULL;
	prj->last_cmd = NULL;
	prj->env = NULL;
	prj->env_str = NULL;
	prj->paths = NULL;
	prj->name = NULL;
	prj->argv = NULL;
	prj->our_path = NULL;
}

void	init_prj(t_prj *prj, char **env)
{
	null_struct(prj);
	took_env(prj, env);
	prj->env_str = make_env_str(prj->env);
	prj->pid = 0;
	prj->skip = 0;
	prj->our_path = getcwd(NULL, 1024);
	prj->name = ft_strdup(NAME, 0);
}
