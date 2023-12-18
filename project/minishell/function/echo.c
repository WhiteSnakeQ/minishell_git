/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abobylev <abobylev@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:07:01 by abobylev          #+#    #+#             */
/*   Updated: 2023/12/17 21:07:05 by abobylev         ###   ########.fr       */
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
