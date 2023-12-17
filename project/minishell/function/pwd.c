/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 09:34:47 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	pwd(char **strs, t_prj *prj, int fd)
{
	char	*path;

	if (!strs)
		return ;
	path = getcwd(NULL, 1024);
	if (!path)
	{
		ft_printf(fd, "%s\n", prj->our_path);
		prj->exit = 0;
		return ;
	}
	ft_printf(fd, "%s\n", path);
	free_string(path);
	prj->exit = 0;
	return ;
}
