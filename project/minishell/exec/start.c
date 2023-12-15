/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   start.c											:+:		:+:	:+:   */
/*													+:+ +:+			+:+	 */
/*   By: codespace <codespace@student.42.fr>		+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2023/12/11 00:14:32 by kreys				#+#	#+#			 */
/*   Updated: 2023/12/14 22:09:43 by codespace		###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	write_in_fd(t_cmd *cmd, t_cmd *cmd2)
{
	if (!cmd2)
		return ;
	close(cmd->pipe[1]);
	cmd2->redirect_inp = 1;
	cmd2->file_inp = cmd->pipe[0];
}

static void	worket(t_prj *prj, t_cmd *cmd)
{
	if (my_execve(prj, cmd) == 1)
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			exit(print_error(PEDERR));
		if (cmd->pid == 0)
		{
			if (cmd->next && cmd->redirect_out == 0)
				dup2(cmd->pipe[1], STDOUT_FILENO);
			else if (cmd->redirect_out == 1)
				dup2(cmd->file_fd_out, STDOUT_FILENO);
			if (cmd->redirect_inp == 1 || cmd->redirect_inp == 2)
				dup2(cmd->file_inp, STDIN_FILENO);
			if (cmd->file_inp != 0)
				close(cmd->file_inp);
			execve(cmd->cmd_name, cmd->argv, prj->env_str);
			ft_printf(2, "minishell: %s: command not found\n", cmd->argv[0]);
			exit(127);
		}
	}
	prj->pid = cmd->pid;
	write_in_fd(cmd, cmd->next);
}

static void	helper_exv(t_cmd **cmd)
{
	*cmd = (*cmd)->next;
	close((*cmd)->pipe[1]);
	(*cmd)->file_inp = (*cmd)->pipe[0];
	(*cmd)->redirect_inp = 1;
}

static void	end_ex(t_prj *prj, int j, int i)
{
	waitpid(j, &prj->exit, 0);
	waitpid(i, &prj->exit, 0);
	prj->last_cmd = ft_itoa(prj->exit % 255, prj->last_cmd);
}

void	execute_cmd(t_prj *prj, t_cmd *cmd)
{
	t_helper	help;

	help.j = 0;
	while (cmd)
	{
		if (cmd->valid <= 0 || (cmd->valid == 3 && prj->exit == 0)
			|| (cmd->valid == 2 && prj->exit != 0))
		{
			if (cmd->valid == 3)
				break ;
			helper_exv(&cmd);
			continue ;
		}
		if (cmd->valid == 3 || cmd->valid == 2)
			waitpid(help.j, &prj->exit, 0);
		if (ft_strcmp(cmd->argv[0], "exit") == 0)
			exit_m(cmd->argv, prj);
		worket(prj, cmd);
		if (help.j == 0)
			help.j = cmd->pid;
		help.i = cmd->pid;
		cmd = cmd->next;
	}
	end_ex(prj, help.j, help.i);
}
