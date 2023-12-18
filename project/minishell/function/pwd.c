/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abobylev <abobylev@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:07:28 by abobylev          #+#    #+#             */
/*   Updated: 2023/12/17 21:07:30 by abobylev         ###   ########.fr       */
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
