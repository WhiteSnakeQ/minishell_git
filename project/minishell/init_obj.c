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

void	took_env(t_prj *prj, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			break ;
		i++;
	}
	prj->paths = ft_split(&env[i][5], ':');
}

void	init_prj(t_prj *prj, char **env)
{
	took_env(prj, env);
	prj->env = env;
	prj->exit = 0;
	prj->pid = 0;
	prj->our_path = ft_strdup("./", 0);
	prj->name = ft_strdup(NAME, 0);
	prj->list_argv = NULL;
}
