/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_module.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 01:06:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_one_argv(t_argv *argv)
{
	free_string(argv->text);
	free(argv);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
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
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
	cmd = NULL;
}

void	free_text(t_text *text)
{
	t_text	*next;

	while (text)
	{
		free_string(text->text);
		next = text->next;
		free(text);
		text = next;
	}
	text = NULL;
}

void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		free_string(env->key);
		free_string(env->value);
		next = env->next;
		free(env);
		env = next;
	}
	env = NULL;
}

void	free_argv(t_argv *text)
{
	t_argv	*next;

	while (text)
	{
		free_string(text->text);
		next = text->next;
		free(text);
		text = next;
	}
	text = NULL;
}
