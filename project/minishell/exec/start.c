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

static void	worket(t_prj *prj, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(print_error(PEDERR));
	if (cmd->pid == 0)
	{
		if (my_execve(prj, cmd, 0) == -1)
			exit(0);
		if (cmd->next && cmd->next->valid >= 2)
			dup2(STDOUT_FILENO, STDOUT_FILENO);
		else if (cmd->next && cmd->redirect_out == 0)
			dup2(cmd->pipe[1], STDOUT_FILENO);
		else if (cmd->redirect_out == 1)
			dup2(cmd->file_fd_out, STDOUT_FILENO);
		if (cmd->redirect_inp == 1 || cmd->redirect_inp == 2)
			dup2(cmd->file_inp, STDIN_FILENO);
		close_all(prj);
		execve(cmd->cmd_name, cmd->argv, prj->env_str);
		exit(127);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	prj->pid = cmd->pid;
	write_in_fd(cmd, cmd->next);
}

static void	end_ex(t_prj *prj, int j, int i, int mod)
{
	if (mod != 1)
	{
		prj->l_cmd = ft_itoa(prj->exit % 255, prj->l_cmd);
		return ;
	}
	if (i != 0)
		waitpid(j, &prj->exit, 0);
	if (i != j && i != 0)
		waitpid(i, &prj->exit, 0);
	prj->l_cmd = ft_itoa(prj->exit % 255, prj->l_cmd);
}

static void	check_cmd_emp(t_cmd **cmd, t_prj *prj)
{
	void	*dir;
	t_cmd	*cm;

	cm = *cmd;
	if ((*cmd)->cmd_name[0] == '\0')
		(*cmd) = (*cmd)->next;
	if (cm->valid == 3 && prj->exit == 0)
		return ;
	if (check_all_cmd(cm->cmd_name) == 1)
		prj->exit = prj->exit;
	else if (cm->cmd_name)
	{
		cm->cmd_name = took_puth(prj, cm);
		dir = opendir(cm->cmd_name);
		if (access(cm->cmd_name, X_OK) != 0 || dir)
		{
			if (dir)
				closedir(dir);
			prj->exit = 127;
			cm->valid = -1;
			ft_printf(2, "minishell: %s: command not found\n", \
				cm->argv[0]);
		}
	}
}

void	execute_cmd(t_prj *prj, t_cmd *cmd, int f_ex, int l_ex)
{
	int	mod;

	while (cmd)
	{
		mod = 1;
		check_cmd_emp(&cmd, prj);
		if (cmd->valid <= 0 || (cmd->valid == 3 && prj->exit == 0)
			|| (cmd->valid == 2 && prj->exit == 0))
		{
			if ((cmd->valid <= 0 && !cmd->next) || (cmd->valid == 3))
				break ;
		}
		if (!prj->cmd->next || (cmd->next && cmd->next->valid >= 2))
			mod = my_execve(prj, cmd, 1);
		if (mod == 1)
			worket(prj, cmd);
		if (f_ex == 0)
			f_ex = cmd->pid;
		l_ex = cmd->pid;
		cmd = cmd->next;
		if (cmd && (cmd->valid == 3 || cmd->valid == 2))
			waitpid(l_ex, &prj->exit, 0);
	}
	end_ex(prj, f_ex, l_ex, mod);
}
