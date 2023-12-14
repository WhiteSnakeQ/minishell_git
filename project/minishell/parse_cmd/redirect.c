/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 14:21:37 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void    close_if_op(t_cmd *cmd, int mod)
{
    if (mod == 0)
    {
        if (cmd->file_inp != 0)
        close (cmd->file_inp);
    }
    else
    {
        if (cmd->file_fd_out != 1)
        close (cmd->file_fd_out);
    }
}

void    change_fd_write(t_cmd *cmd, int mod, char *str)
{
    close_if_op(cmd, 1);
    cmd->redirect_out = 1;
    if (mod == SINGLE)
    {
        cmd->file_fd_out = open(str, O_WRONLY | O_CREAT | O_TRUNC, 777);
        if (cmd->file_fd_out < 0)
        {
            ft_printf(2, "minishell: ");
            perror(str);
            cmd->valid = 0;
            return ;
        }
    }
    else
    {
        cmd->file_fd_out = open(str, O_APPEND | O_CREAT, 777);
        if (cmd->file_fd_out < 0)
        {
            ft_printf(2, "minishell: ");
            perror(str);
            cmd->valid = 0;
            return ;
        }
    }
}

static void    read_term(t_prj *prj, t_cmd *cmd, char *stop)
{
    char *fr_term;

    (void)prj;
    pipe(cmd->pipe);
    fr_term = get_next_line(0);
    while (fr_term && ft_strncmp(stop, fr_term, ft_strlen(fr_term) - 1) != 0)
    {
        ft_printf(cmd->pipe[1], fr_term);
        free_string(fr_term);
        fr_term = get_next_line(0);
    }
    close(cmd->pipe[1]);
    free_string(fr_term);
    if (!cmd->next)
        return ;
    if (cmd->next->redirect_inp != 1 && cmd->next->valid == 1)
    {
        cmd->next->redirect_inp = 1;
        cmd->next->file_inp = cmd->pipe[0];
    }
}

void    change_fd_read(t_cmd *cmd, int mod, char *str, t_prj *prj)
{
    close_if_op(cmd, 0);
    if (cmd->valid == 0)
        return ;
    cmd->redirect_inp = 1;
    if (mod == SINGLE)
    {
        cmd->file_inp = open(str, O_RDONLY);
        if (cmd->file_inp < 0)
        {
            ft_printf(2, "minishell: ");
            perror(str);
            cmd->valid = 0;
            return ;
        }
    }
    else
        read_term(prj, cmd, str);
}
