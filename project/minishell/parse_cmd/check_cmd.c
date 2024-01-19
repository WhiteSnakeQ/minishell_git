/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 07:39:09 by kreys             #+#    #+#             */
/*   Updated: 2024/01/19 16:06:37 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*took_puth(t_prj *prj, t_cmd *cmd)
{
	int		i;
	char	*cheack;
	char	*midl;

	i = 0;
	if (cmd->cmd_name[0] == '\\' || !prj->paths)
		return (cmd->cmd_name);
	while (prj->paths[i])
	{
		cheack = ft_strjoin(prj->paths[i], "/");
		midl = ft_strjoin(cheack, cmd->argv[0]);
		free(cheack);
		cheack = midl;
		if (access(cheack, X_OK) == 0)
		{
			free_string(cmd->cmd_name);
			return (cheack);
		}
		free(cheack);
		i++;
	}
	return (cmd->cmd_name);
}

int	check_all_cmd(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "echo") == 0)
		i++;
	else if (ft_strcmp(str, "cd") == 0)
		i++;
	else if (ft_strcmp(str, "pwd") == 0)
		i++;
	else if (ft_strcmp(str, "exit") == 0)
		i++;
	else if (ft_strcmp(str, "export") == 0)
		i++;
	else if (ft_strcmp(str, "env") == 0)
		i++;
	else if (ft_strcmp(str, "unset") == 0)
		i++;
	return (i);
}

int	make_tild(char *str, t_prj *prj, int *srt, char *ret)
{
	int		to_ret;
	int		i;
	char	*value;

	to_ret = 1;
	if (!str[to_ret] || str[to_ret] == '/')
	{
		value = get_value_env_str("HOME", prj->env);
		i = -1;
		while (value[++i])
		{
			ret[*srt] = value[i];
			*srt += 1;
		}
		if (str[to_ret])
		{
			to_ret++;
			ret[*srt] = '/';
		}
		return (to_ret);
	}
	ret[*srt] = '~';
	*srt += 1;
	return (to_ret);
}
