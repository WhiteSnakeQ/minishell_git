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

static int  check_token(char *str)
{
    int i;

    i = 0;
    if (ft_strcmp(str, "|") == 0)
        i = 1;
    if (ft_strcmp(str, ">>") == 0 \
                || ft_strcmp(str, "<<") == 0 \
                || ft_strcmp(str, "<") == 0 \
                || ft_strcmp(str, ">") == 0)
    {
        if (i == 0)
        {
            ft_printf(2, "%s`%s'\n", UNEXPTOKS, str);
            return (-1);
        }
        ft_printf(2, "%s`%s'\n", UNEXPTOKS, str);
        return (-1);
    }
    if (ft_strcmp(str, "|") == 0)
    {
        ft_printf(2, "%s`%s'\n", UNEXPTOKS, str);
        return (-1);
    }
    return (0);
}

int    check_sp_smb_arv(t_argv *argv)
{
    if (ft_strcmp(argv->text, "|") == 0)
    {
        ft_printf(2, UNEXPTOK);
        return (-1);
    }
    while (argv)
    {
        if (argv->next)
        {
            if (ft_strcmp(argv->text, ">>") == 0 \
                || ft_strcmp(argv->text, "<<") == 0 \
                || ft_strcmp(argv->text, "<") == 0 \
                || ft_strcmp(argv->text, ">") == 0 \
                || ft_strcmp(argv->text, "|") == 0)
            {
                if  (check_token(argv->next->text) == -1)
                    return (-1);
            }
        }
        if (!argv->next)
        {
            if (ft_strcmp(argv->text, ">>") == 0 \
                || ft_strcmp(argv->text, "<<") == 0 \
                || ft_strcmp(argv->text, "<") == 0 \
                || ft_strcmp(argv->text, ">") == 0)
            {
                ft_printf(2, UNEXPTOKN);
                    return (-1);
            }
            else if (ft_strcmp(argv->text, "|") == 0)
            {
                ft_printf(2, UNEXPTOK);
                    return (-1);
            }
            else if (ft_strcmp(argv->text, "&&") == 0 || ft_strcmp(argv->text, "||") == 0)
            {
                ft_printf(2, "%s`%s'\n", UNEXPTOKS, argv->text);
                    return (-1);
            }
        }
        argv = argv->next;
    }
    return (0);
}