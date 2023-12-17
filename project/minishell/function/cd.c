/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 01:15:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*change_env(char *new_pwd, t_prj *prj, int fd)
{
	if (!new_pwd)
		new_pwd = ft_strdup(get_value_env_str("HOME", prj->env), 0);
	else
		new_pwd = ft_strdup(new_pwd, 0);
	if (!new_pwd)
		return (NULL);
	if (ft_strcmp(new_pwd, "-") == 0)
	{
		if (ft_strcmp(get_value_env_str("PWD", prj->env), "/") != 0)
		{
			free_string(new_pwd);
			new_pwd = ft_strdup((get_value_env_str("HOME", prj->env), "/"), 0);
		}
		else
		{
			free_string(new_pwd);
			new_pwd = ft_strdup(get_value_env_str("OLDPWD", prj->env), 0);
		}
		if (new_pwd)
			ft_printf(fd, "%s\n", new_pwd);
	}
	if (get_value_env_str("OLDPWD", prj->env))
		env_change_key(prj, "OLDPWD", get_value_env_str("PWD", prj->env));
	return (new_pwd);
}

static void	re_lock(void *dir, char *path)
{
	closedir(dir);
	chdir(path);
}

static void	set_root(t_prj *prj)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (get_value_env_str("PWD", prj->env))
		env_change_key(prj, "PWD", pwd);
	free_string(pwd);
}

static int	error_handle(char **strs, t_prj *prj)
{
	char	*oldpwd;
	char	*home;

	oldpwd = get_value_env_str("OLDPWD", prj->env);
	home = get_value_env_str("HOME", prj->env);
	if (strs[1] && strs[2])
	{
		ft_printf(2, INVNARG);
		return (-1);
	}
	else if (strs[1] && ft_strcmp(strs[1], "-") == 0 && oldpwd == NULL)
	{
		ft_printf(2, CDOLD);
		return (-1);
	}
	else if (!strs[1] && !home)
	{
		ft_printf(2, CDHOME);
		return (-1);
	}
	return (0);
}

void	cd(char **strs, t_prj *prj, int fd)
{
	void	*dir;
	char	*path;

	prj->exit = 1;
	if (error_handle(strs, prj) == -1)
		return ;
	path = change_env(strs[1], prj, fd);
	dir = opendir(path);
	if (dir == 0)
	{
		if (strs[1])
			ft_printf(2, "minishell: cd: %s: ", strs[1]);
		else
			ft_printf(2, "minishell: cd: %s: ", path);
		perror(NULL);
		free_string(path);
		return ;
	}
	re_lock(dir, path);
	free_string(path);
	set_root(prj);
	prj->exit = 0;
}
