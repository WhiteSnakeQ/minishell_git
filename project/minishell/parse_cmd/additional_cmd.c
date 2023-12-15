/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/15 01:54:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_cmd(t_argv **argv)
{
	if (!*argv)
		return (-1);
	if (ft_strcmp((*argv)->text, "||") == 0 && (*argv)->ex == 1)
		return (-1);
	if (ft_strcmp((*argv)->text, "&&") == 0 && (*argv)->ex == 1)
		return (-1);
	if (ft_strcmp((*argv)->text, "|") == 0 && (*argv)->ex == 1)
	{
		*argv = (*argv)->next;
		return (-1);
	}
	return (0);
}
