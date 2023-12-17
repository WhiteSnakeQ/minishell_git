/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 02:21:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	exit_mod(t_prj *prj, t_cmd *cmd, int mod)
{
	if (mod == 1)
		ft_printf(1, "exit\n");
	exit_m(cmd->argv, prj);
}

static int	set_signal(void)
{
	signal(SIGQUIT, signal_quit);
	signal(SIGINT, signal_sig);
	return (1);
}int	my_execve(t_prj *prj, t_cmd *cmd, int mod)
{
	int	fd;

	fd = cmd->pipe[1];
	if (!cmd->next)
		fd = 1;
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		echo(cmd->argv, prj, fd);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		cd(cmd->argv, prj, fd);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		pwd(cmd->argv, prj, fd);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		exit_mod(prj, cmd, mod);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		export(cmd->argv, prj, fd);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		env(cmd->argv, prj, fd);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		unset(cmd->argv, prj);
	else
		return (set_signal());
	return (-1);
}
