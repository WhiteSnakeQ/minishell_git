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

void    add_last_cmd(t_cmd **cmd, t_cmd *new)
{
    t_cmd   *curr;

    curr = *cmd;
    if (!*cmd)
    {
        *cmd = new;
        return ;
    }
    while (curr->next)
        curr = curr->next;
    curr->next = new;
}
