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

static void	write_in_fd(t_prj *prj, t_cmd *cmd)
{
	char	*str;

    pipe(prj->pipeold);
    close(prj->pipe[1]);
    ft_printf(2,"%d\n", cmd->file_fd_out);
    if (cmd->next && cmd->next->redirect_inp == 2)
    {
        cmd->file_fd_out = prj->pipeold[1];
    }  
	str = get_next_line(prj->pipe[0]);
	while (str)
	{
		ft_printf(cmd->file_fd_out, "%s", str);
		free(str);
		str = get_next_line(prj->pipe[0]);
	}
	close(prj->pipe[0]);
    close(prj->pipeold[1]);
}

static void	worket(t_prj *prj, t_cmd *cmd)
{
    if (pipe(cmd->pipe) == -1)
		exit(print_error(PIPERR));
    prj->pipe = cmd->pipe;
    if (my_execve(prj, cmd) == 1)
	{
        cmd->pid = fork();
	    if (cmd->pid == -1)
		    exit(print_error(PEDERR));
	    if (cmd->pid == 0)
	    {
                if (cmd->redirect_inp == 2)
                dup2(prj->pipeold[0], STDIN_FILENO);
            close(prj->pipeold[1]);
		    dup2(prj->pipe[1], STDOUT_FILENO);
		    if (cmd->redirect_inp == 1)
                dup2(cmd->file_inp, STDIN_FILENO);
            close(prj->pipe[0]);
		    execve(cmd->cmd_name, cmd->argv, prj->env_str);
            ft_printf(2, "minishell: %s: command not found\n", cmd->argv[0]);
            exit(127);
	    }
    }
    prj->pid = cmd->pid;
    if (!cmd->next)
        return ;
    if (cmd->next->redirect_inp != 1 && cmd->next->valid == 1)
        cmd->next->redirect_inp = 2;
}

void    execute_cmd(t_prj *prj)
{
    t_cmd   *cmd;

    cmd = prj->cmd;
    while (cmd)
    {
        if (cmd->valid <= 0 || (cmd->valid == 3 && prj->exit == 0) \
            || (cmd->valid == 2 && prj->exit != 0))
        {
            if (cmd->valid == 3)
                write_in_fd(prj, cmd);
            cmd = cmd->next;
            continue ;
        }
        if (ft_strcmp(cmd->argv[0], "exit") == 0)
        {
            close(prj->pipeold[0]);
            close(prj->pipeold[1]);
            free(prj->pipeold);
            exit_m(cmd->argv, prj);
        }
        worket(prj, cmd);
        waitpid(cmd->pid, &prj->exit, 0);
        prj->last_cmd = ft_itoa(prj->exit % 255, prj->last_cmd);
        write_in_fd(prj, cmd);
        cmd = cmd->next;
    }
}
