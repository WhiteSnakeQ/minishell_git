/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 14:10:12 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char    *took_puth(t_prj *prj, t_cmd *cmd)
{
	int		i;
	char	*cheack;
	char	*midl;

	i = 0;
    if (cmd->cmd_name[0] == '\\' || !prj->paths)
    {
        return (cmd->cmd_name);
    }
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

int    my_execve(t_prj *prj, t_cmd *cmd)
{
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
        echo(cmd->argv, prj);
    else if (ft_strcmp(cmd->argv[0], "cd") == 0)
        cd(cmd->argv, prj);
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        pwd(cmd->argv, prj);
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        exit_m(cmd->argv, prj);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        export(cmd->argv, prj);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        env(cmd->argv, prj);
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        unset(cmd->argv, prj);
    else
    {
        cmd->cmd_name = took_puth(prj, cmd);
        return (1);
    }
    return (-1);
}