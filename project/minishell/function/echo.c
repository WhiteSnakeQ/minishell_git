/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/15 14:27:05 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	skip_n(char **strs, int *nl)
{
	int	i;

	i = 1;
	if (!strs[i])
		return (1);
	while (strs[i] && ft_strcmp(strs[i], "-n") == 0)
	{
		i++;
		*nl = 0;
	}
	return (i);
}

void	echo(char **strs, t_prj *prj, int fd)
{
	int	nl;
	int	i;

	nl = 1;
	i = 0;
	i = skip_n(strs, &nl);
	if (!strs)
	{
		prj->exit = 0;
		return ;
	}
	while (strs[i])
	{
		ft_printf(fd, "%s", strs[i++]);
		if (strs[i])
			ft_printf(fd, " ");
	}
	if (nl == 1)
		ft_printf(fd, "\n");
	prj->exit = 0;
	return ;
}
