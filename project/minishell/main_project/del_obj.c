/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/18 12:39:34 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_one_cmd(t_cmd *cmd)
{
	free_string(cmd->cmd_name);
	free_strings(cmd->argv);
	close_fd(cmd->pipe[1]);
	close_fd(cmd->pipe[0]);
	close_fd(cmd->file_inp);
	close_fd(cmd->file_fd_out);
	if (cmd->file_fd_out != 0 && cmd->file_fd_out != 1)
		close(cmd->file_fd_out);
	free(cmd->pipe);
	free(cmd);
}

void	clean_dirty(t_prj *prj)
{
	prj->pid = 0;
	free_argv(prj->list_argv);
	prj->list_argv = NULL;
	free_string(prj->argv);
	prj->argv = NULL;
	free_cmd(prj->cmd);
	prj->cmd = NULL;
	close_fd(prj->pipeold[1]);
	close_fd(prj->pipeold[0]);
}

void	clean_prj(int mod, t_prj **prj)
{
	static t_prj	*to_clean = NULL;

	if (mod == SET)
	{
		to_clean = *prj;
		return ;
	}
	if (!to_clean)
		return ;
	free_string(to_clean->name);
	free_string(to_clean->our_path);
	free_string(to_clean->argv);
	free_string(to_clean->l_cmd);
	free_strings(to_clean->paths);
	free_strings(to_clean->env_str);
	free_cmd(to_clean->cmd);
	free_argv(to_clean->list_argv);
	free_env(to_clean->env);
	if (to_clean->pipeold)
		free(to_clean->pipeold);
	free(to_clean);
	close(0);
	close(1);
	close(2);
}
