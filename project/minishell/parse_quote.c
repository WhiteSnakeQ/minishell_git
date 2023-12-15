/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:21:42 by codespace         #+#    #+#             */
/*   Updated: 2023/12/14 22:41:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	calc_g_env(char *str, t_prj *prj, int *stop, int i)
{
	int		j;
	char	*key;

	j = -1;
	*stop += 1;
	if (str[i] == '$')
		return (1);
	if (str[i] == '?')
		return (ft_strlen(prj->last_cmd));
	*stop -= 1;
	while (str[i] && (str[i] != ' ' && str[i] != '$' && str[i] != '\''
			&& str[i] != '\"'))
	{
		if ((str[i] >= '0' && str[i] <= '9') && i == 0)
		{
			*stop += 1;
			return (0);
		}
		i++;
	}
	if (i == 0)
		return (0);
	key = create_str(i);
	while (++j < i)
		key[j] = str[j];
	*stop += i;
	i = get_value_env_int(key, prj->env);
	free_string(key);
	return (i);
}

static int	calc_d_q(char *str, t_prj *prj, int *stop)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i] != '\"')
	{
		if (str[i] == '$' && i++ > -1)
			size += calc_g_env(&str[i], prj, &i, 0);
		else
		{
			i++;
			size++;
		}
	}
	*stop += i;
	return (size);
}

static int	calc_s_q(char *str, int *stop)
{
	int	i;

	i = 0;
	while (str[i] != '\'')
		i++;
	*stop += i;
	return (i);
}

static int	check_doubl_q(char *str, t_prj *prj, t_argv *argv, int i)
{
	int	size;

	size = 0;
	while (str[i])
	{
		if (str[i] == '\"' && i++ > -1)
		{
			size += calc_d_q(&str[i], prj, &i);
			if (str[i])
				i++;
			argv->ex = 0;
		}
		else if (str[i] == '\'' && i++ > -1)
		{
			size += calc_s_q(&str[i], &i);
			if (str[i])
				i++;
			argv->ex = 0;
		}
		else if (str[i] == '$' && i++ > -1)
			size += calc_g_env(&str[i], prj, &i, 0);
		else if (i++ > -1)
			size++;
	}
	return (size);
}

void	parse_quotet(t_prj *prj)
{
	t_argv	*argv;
	int		i;

	argv = prj->list_argv;
	while (argv)
	{
		argv->ex = 1;
		i = check_doubl_q(argv->text, prj, argv, 0);
		argv->text = make_full(argv->text, prj, i, 0);
		argv = argv->next;
	}
}
