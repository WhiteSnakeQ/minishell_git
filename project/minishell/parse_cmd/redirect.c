/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2024/01/09 10:55:48 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_if_op(t_cmd *cmd, int mod)
{
	if (mod == 0)
	{
		if (cmd->file_inp != 0 && cmd->file_inp != 1)
			close(cmd->file_inp);
	}
	else
	{
		if (cmd->file_fd_out != 1 && cmd->file_fd_out != 0)
			close(cmd->file_fd_out);
	}
}

void	change_fd_write(t_cmd *cmd, int mod, char *str)
{
	close_if_op(cmd, 1);
	cmd->redirect_out = 1;
	if (mod == SINGLE && str[0] != '$')
	{
		cmd->file_fd_out = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->file_fd_out < 0)
		{
			ft_printf(2, "minishell: ");
			perror(str);
			cmd->valid = 0;
		}
	}
	else if (str[0] != '$')
	{
		cmd->file_fd_out = open(str, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (cmd->file_fd_out < 0)
		{
			ft_printf(2, "minishell: ");
			perror(str);
			cmd->valid = 0;
		}
	}
	else
		ft_printf(2, "minishell: %s: ambiguous redirect\n", str);
}

int	scan(char *str, char *str2)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str2[i] == '\n' && str[i])
			return (1);
		if (str[i] != str2[i])
			return (str[i] - str2[i]);
	}
	if (str2[i] == '\n' && str[i] == '\0')
		return (0);
	return (str[i] - str2[i]);
}

static void	read_term(t_prj *prj, t_cmd *cmd, char *stop)
{
	char	*fr_term;

	close_fd_two(prj->pipeold[0], prj->pipeold[1]);
	if (pipe(prj->pipeold) == -1)
		exit (print_error(PIPERR));
	ft_printf(2, "> ");
	fr_term = convert_to_normal(get_next_line(0), prj, stop);
	while (fr_term && scan(stop, fr_term) != 0)
	{
		ft_printf(2, "> ");
		ft_printf(prj->pipeold[1], fr_term);
		free_string(fr_term);
		fr_term = convert_to_normal(get_next_line(0), prj, stop);
	}
	free_string(fr_term);
	close(prj->pipeold[1]);
	cmd->file_inp = prj->pipeold[0];
	if (cmd->redirect_inp != 1)
		cmd->redirect_inp = 2;
}

void	change_fd_read(t_cmd *cmd, int mod, char *str, t_prj *prj)
{
	close_if_op(cmd, 0);
	if (mod == SINGLE)
	{
		if (cmd->valid == 0)
			return ;
		cmd->redirect_inp = 1;
		cmd->file_inp = open(str, O_RDONLY);
		if (cmd->file_inp < 0)
		{
			ft_printf(2, "minishell: ");
			perror(str);
			close(cmd->pipe[1]);
			close(cmd->pipe[0]);
			cmd->valid = 0;
			return ;
		}
	}
	else
	{
		set_signal_ignore();
		read_term(prj, cmd, str);
		set_signal_ignore();
	}
}
