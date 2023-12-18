/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/18 12:44:18 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	make_list_env(char **env, t_prj *prj)
{
	int	i;

	i = 0;
	while (env && env[i])
	env_add_last(prj, env[i++]);
}

void	took_env(t_prj *prj, char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			break ;
		i++;
	}
	if (env[i])
		prj->paths = ft_split(&env[i][5], ':');
	make_list_env(env, prj);
}

static void	null_struct(t_prj *prj)
{
	prj->list_argv = NULL;
	prj->l_cmd = NULL;
	prj->env = NULL;
	prj->env_str = NULL;
	prj->paths = NULL;
	prj->name = NULL;
	prj->argv = NULL;
	prj->cmd = NULL;
	prj->pipeold = NULL;
}

void	init_prj(t_prj *prj, char **env)
{
	char	*str;

	null_struct(prj);
	took_env(prj, env);
	prj->env_str = make_env_str(prj->env);
	prj->l_cmd = ft_strdup("0", 0);
	prj->pipeold = malloc(sizeof(int) * 2);
	if (!prj->pipeold)
		exit(print_error(MALCERR));
	if (get_value_env_str("SHLVL", prj->env))
	{
		str = ft_itoa(ft_atoi(get_value_env_str("SHLVL", prj->env)) + 1, NULL);
		env_change_key(prj, "SHLVL", str);
		free_string(str);
	}
	prj->pipeold[0] = 0;
	prj->pipeold[1] = 0;
	prj->our_path = getcwd(NULL, 1024);
	prj->pid = 0;
	prj->skip = 0;
	prj->exit = 0;
	prj->name = ft_strdup(NAME, 0);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit(print_error(MALCERR));
	cmd->pipe = malloc(sizeof(int) * 2);
	if (pipe(cmd->pipe) == -1)
		exit(print_error(PIPERR));
	cmd->valid = 1;
	cmd->redirect_inp = 0;
	cmd->file_fd_out = 1;
	cmd->file_inp = 0;
	cmd->redirect_out = 0;
	cmd->next = NULL;
	cmd->cmd_name = NULL;
	cmd->argv = NULL;
	return (cmd);
}
