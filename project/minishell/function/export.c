/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 01:53:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	add_puth(t_prj *prj)
{
	int	i;

	i = 0;
	while (prj->env_str[i])
	{
		if (ft_strncmp("PATH", prj->env_str[i], 4) == 0)
			break ;
		i++;
	}
	if (prj->env_str[i])
		prj->paths = ft_split(&prj->env_str[i][5], ':');
	else
		prj->paths = NULL;
}

static void	add_some_th(char *strs, t_prj *prj)
{
	char	*key;
	char	*new_val;

	if ((strs[0] >= '0' && strs[0] <= '9') || symbl_in_str(strs, ' ') == 1)
	{
		ft_printf(2, "minishell: export: `%s':%s\n", strs, NVID);
		return ;
	}
	else
	{
		key = new_str_till(strs, '=');
		new_val = new_str_after(strs, '=');
		if (env_cahnge_key2(prj, key, new_val) != 1)
			env_add_last(prj, strs);
		free_string(key);
		free_string(new_val);
	}
}

static int	size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static void	print_exp(t_env *env, int fd)
{
	t_env	*curr;
	char	**strs;
	int		i;
	int		size;

	i = 0;
	curr = env;
	size = size_env(env);
	strs = export_all(curr, size);
	ft_sort_params(strs, size);
	while (strs[i])
		ft_printf(fd, "declare -x %s\n", strs[i++]);
	free_strings(strs);
}

void	export(char **strs, t_prj *prj, int fd)
{
	int	i;

	i = 1;
	while (strs[i])
		add_some_th(strs[i++], prj);
	if (!strs[1])
		print_exp(prj->env, fd);
	else
	{
		free_strings(prj->env_str);
		prj->env_str = make_env_str(prj->env);
		free_strings(prj->paths);
		add_puth(prj);
	}
	prj->exit = 0;
	return ;
}
