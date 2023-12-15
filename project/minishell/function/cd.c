/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/15 00:45:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*change_env(char *new_pwd, t_prj *prj, int fd)
{
	if (!new_pwd)
		new_pwd = ft_strdup(get_value_env_str("HOME", prj->env), 0);
	else
		new_pwd =  ft_strdup(new_pwd, 0);
	if (ft_strcmp(new_pwd, "-") == 0)
	{
		if (ft_strcmp())
		free(new_pwd);
		ft_printf(fd, "%s\n", get_value_env_str("PWD", prj->env));
		new_pwd = ft_strdup(get_value_env_str("OLDPWD", prj->env), 0);
	}
	env_change_key(prj, "OLDPWD", get_value_env_str("PWD", prj->env));
	env_change_key(prj, "PWD", new_pwd);
	return (new_pwd);
}

static void	re_lock(void *dir, t_prj *prj, char *path)
{
	closedir(dir);
	free_string(prj->our_path);
	chdir(path);
	prj->our_path = getcwd(NULL, 1024);
}

void	cd(char **strs, t_prj *prj, int fd)
{
	void	*dir;
	char	*path;

	prj->exit = 1;
	if (strs[1] && strs[2])
	{
		ft_printf(2, INVNARG);
		return ;
	}
	path = change_env(strs[1], prj, fd);
	dir = opendir(path);
	if (dir == 0)
	{
		ft_printf(2, "minishell: %s: ", strs[1]);
		perror(NULL);
		return ;
	}
	else
		re_lock(dir, prj, path);
	prj->exit = 0;
	free_string(path);
}
