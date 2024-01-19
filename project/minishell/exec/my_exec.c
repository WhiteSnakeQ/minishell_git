/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:06:21 by abobylev          #+#    #+#             */
/*   Updated: 2024/01/19 16:44:32 by kreys            ###   ########.fr       */
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
}

static void	check_terminal(t_cmd *cmd)
{
	if (cmd && cmd->next && cmd->next->valid >= 2)
		cmd->file_fd_out = 1;
}

int	my_execve(t_prj *prj, t_cmd *cmd, int mod)
{
	int	fd;

	fd = cmd->pipe[1];
	check_terminal(cmd);
	if (cmd->redirect_out == 1 || !cmd->next)
		fd = cmd->file_fd_out;
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
