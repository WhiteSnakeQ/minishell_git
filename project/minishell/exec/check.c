/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 07:51:35 by kreys             #+#    #+#             */
/*   Updated: 2023/12/15 08:58:09 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_token(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "|") == 0)
		i = 1;
	if (ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0 || ft_strcmp(str,
			"<") == 0 || ft_strcmp(str, ">") == 0)
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

static int	check_token2(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (-1);
	if (ft_strcmp(str, "||") == 0)
		return (-1);
	if (ft_strcmp(str, "&&") == 0)
		return (-1);
	return (0);
}

static int	check_next(t_argv *argv)
{
	if (ft_strcmp(argv->text, ">>") == 0 || \
		ft_strcmp(argv->text, "<<") == 0 || \
			ft_strcmp(argv->text, "<") == 0 \
				|| ft_strcmp(argv->text, ">") == 0)
	{
		if (check_token(argv->next->text) == -1)
			return (-1);
	}
	else if (ft_strcmp(argv->text, "|") == 0)
	{
		if (check_token2(argv->next->text) == -1)
			return (ft_printf(2, "%s`%s'\n", UNEXPTOKS, argv->text), -1);
	}
	else if (ft_strcmp(argv->text, "&&") == 0 || \
		ft_strcmp(argv->text, "||") == 0)
	{
		if (check_token2(argv->next->text) == -1)
			return (ft_printf(2, "%s`%s'\n", UNEXPTOKS, argv->text), -1);
	}
	return (0);
}

int	check_sp_smb_arv(t_argv *argv)
{
	if (ft_strcmp(argv->text, "|") == 0)
		return (ft_printf(2, UNEXPTOK), -1);
	while (argv)
	{
		if (argv->next)
			if (check_next(argv) == -1)
				return (-1);
		if (!argv->next)
		{
			if (ft_strcmp(argv->text, ">>") == 0 || ft_strcmp(argv->text,
					"<<") == 0 || ft_strcmp(argv->text, "<") == 0
				|| ft_strcmp(argv->text, ">") == 0)
				return (ft_printf(2, UNEXPTOKN), -1);
			else if (ft_strcmp(argv->text, "|") == 0)
				return (ft_printf(2, UNEXPTOK), -1);
			else if (ft_strcmp(argv->text, "&&") == 0 || ft_strcmp(argv->text,
					"||") == 0)
				return (ft_printf(2, "%s`%s'\n", UNEXPTOKS, argv->text), -1);
		}
		argv = argv->next;
	}
	return (0);
}
