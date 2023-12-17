/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 07:39:09 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 00:48:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*took_puth(t_prj *prj, t_cmd *cmd)
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

int	check_all_cmd(char *str)
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
