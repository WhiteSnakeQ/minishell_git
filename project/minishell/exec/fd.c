/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abobylev <abobylev@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:06:15 by abobylev          #+#    #+#             */
/*   Updated: 2023/12/17 21:06:18 by abobylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_fd(int fd)
{
	if (fd >= 3)
		close(fd);
}

void	write_in_fd(t_cmd *cmd, t_cmd *cmd2)
{
	close_fd(cmd->pipe[1]);
	close_fd(cmd->file_inp);
	close_fd(cmd->file_fd_out);
	if (!cmd2 || cmd2->valid == 2 || cmd2->valid == 3)
	{
		close(cmd->pipe[0]);
		return ;
	}
	cmd2->redirect_inp = 1;
	if (cmd2->file_inp == 0)
		cmd2->file_inp = cmd->pipe[0];
	else
		close(cmd->pipe[0]);
}

void	close_all(t_prj *prj)
{
	t_cmd	*start;

	start = prj->cmd;
	while (start)
	{
		close_fd(start->pipe[1]);
		close_fd(start->pipe[0]);
		close_fd(start->file_inp);
		close_fd(start->file_fd_out);
		start = start->next;
	}
}
