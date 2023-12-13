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

#include "../headers/minishell.h"

// void	worket(t_prj *prj)
// {
// 	pid_t	pid;

// 	if (pipe(prj->pipe) == -1)
// 		catch_error(NULL, NULL);
// 	pid = fork();
// 	if (pid == -1)
// 		catch_error(NULL, NULL);
// 	if (pid == 0)
// 	{
// 		dup2(prj->pipe[1], STDOUT_FILENO);
// 		if (i == 1 && prj->file1 != -1)
// 			dup2(prj->file1, STDIN_FILENO);
// 		else if (i == 1 && prj->file1 == -1)
// 		{
// 			clean_all(&prj);
// 			exit(EXIT_FAILURE);
// 		}
// 		close(prj->pipe[0]);
// 		execve(prj->list_cmd->name, prj->list_cmd->cmd, env);
// 		exit(EXIT_FAILURE);
// 	}
// 	remove_cmd(prj);
// 	close(prj->pipe[1]);
// 	dup2(prj->pipe[0], STDIN_FILENO);
// }

t_argv	*check_sp_smb(t_argv *argv, t_cmd *cmd)
{
	if (ft_strcmp(argv->text, ">") == 0)
		change_fd_write(cmd, SINGLE);
	else if (ft_strcmp(argv->text, ">>") == 0)
		change_fd_write(cmd, DOUBLE);
	else if (ft_strcmp(argv->text, "<") == 0)
		change_fd_read(cmd, SINGLE);
	else if (ft_strcmp(argv->text, "<<") == 0)
		change_fd_read(cmd, DOUBLE);
	else
		return (argv);
	return (argv->next->next);
}

t_argv	*create_cmd(t_argv *argv, t_prj *cmd)
{
	t_cmd	*cmd;

	cmd = init_cmd()
	while (argv)
	{
		
	}
	return (argv);
}

void	go_work(t_prj	*prj)
{
	t_argv	*argv;

	argv = prj->list_argv;
	while (argv)
	{
		argv = create_cmd(argv, prj);
	}
}

int	main(int argc, char **argv, char **envs)
{
	t_prj	*prj;

	if (argc != 1 || argv[1])
		return (print_error(ERRARG));
	prj = malloc(sizeof(t_prj));
	if (!prj)
		return (print_error(MALCERR));
	set_signals(prj, SET);
	clean_prj(SET, &prj);
	init_prj(prj, envs);
	while (42)
	{
		set_signals(prj, GET);
		prj->argv = readline(NAME);
		add_history(prj->argv);
		if (!prj->argv)
			exit(print_error("exit\n"));
		parse_argv(prj);
		parse_quotet(prj);
		go_work(prj);
		set_signals(prj, GET);
		clean_dirty(prj);
	}
	return (0);
}
