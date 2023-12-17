/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 07:39:09 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 00:48:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*took_puth(t_prj *prj, t_cmd *cmd)
{
	int		i;
	char	*cheack;
	char	*midl;

	i = 0;
	if (cmd->cmd_name[0] == '\\' || !prj->paths)
		return (cmd->cmd_name);
	while (prj->paths[i])
	{
		cheack = ft_strjoin(prj->paths[i], "/");
		midl = ft_strjoin(cheack, cmd->argv[0]);
		free(cheack);
		cheack = midl;
		if (access(cheack, X_OK) == 0)
		{
			free_string(cmd->cmd_name);
			return (cheack);
		}
		free(cheack);
		i++;
	}
	return (cmd->cmd_name);
}

static int	check_all(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "echo") == 0)
		i++;
	else if (ft_strcmp(str, "cd") == 0)
		i++;
	else if (ft_strcmp(str, "pwd") == 0)
		i++;
	else if (ft_strcmp(str, "exit") == 0)
		i++;
	else if (ft_strcmp(str, "export") == 0)
		i++;
	else if (ft_strcmp(str, "env") == 0)
		i++;
	else if (ft_strcmp(str, "unset") == 0)
		i++;
	return (i);
}

void	check_for_ex(t_prj *prj)
{
	t_cmd	*cmd;
	void	*dir;

	cmd = prj->cmd;
	while (cmd)
	{
		if (check_all(cmd->cmd_name) == 1)
			prj->exit = prj->exit;
		else if (cmd->cmd_name)
		{
			cmd->cmd_name = took_puth(prj, cmd);
			dir = opendir(cmd->cmd_name);
			if (access(cmd->cmd_name, X_OK) != 0 || dir)
			{
				if (dir)
					closedir(dir);
				prj->exit = 127;
				cmd->valid = -1;
				ft_printf(2, "minishell: %s: command not found\n", \
					cmd->argv[0]);
			}
		}
		cmd = cmd->next;
	}
}
