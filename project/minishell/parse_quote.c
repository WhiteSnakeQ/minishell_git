/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:21:42 by codespace         #+#    #+#             */
/*   Updated: 2023/12/16 17:04:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	calc_g_env(char *str, t_prj *prj, int *stop, int i)
{
	int		j;
	char	*key;

	j = check_dollr(str, i, prj);
	if (j != 0 && i++ > -10)
	{
		if (str[1] == '?')
			(*stop)++;
		return ((*stop)++, j);
	}
	while (str[i] && (str[i] != ' ' && str[i] != '$' && str[i] != '\'' \
			&& str[i] != '\"'))
	{
		if ((str[i] >= '0' && str[i] <= '9') && i == 0)
			return (*stop += 1, 0);
		i++;
	}
	if (i == 1)
		return (0);
	key = create_str(i - 1);
	while (++j < i)
		key[j - 1] = str[j];
	return (*stop += i, i = get_value_env_int(key, prj->env), \
		free_string(key), i);
}

static int	calc_d_q(char *str, t_prj *prj, int *stop)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
			size += calc_g_env(&str[i], prj, &i, 0);
		else
		{
			i++;
			size++;
		}
	}
	return (*stop += i, size);
}

static int	calc_s_q(char *str, int *stop)
{
	int	i;

	i = 0;
	while (str[i] != '\'')
		i++;
	return (*stop += i, i);
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
		else if (str[i] == '$')
			size += calc_g_env(&str[i], prj, &i, 0);
		else if (str[i] && i++ > -1)
			size++;
	}
	return (size);
}

void	parse_quotet(t_prj *prj)
{
	t_argv	*argv;
	t_argv	*new;
	t_argv	*prev;
	int		i;

	argv = prj->list_argv;
	while (argv)
	{
		argv->ex = 1;
		i = check_doubl_q(argv->text, prj, argv, 0);
		argv->text = make_full(argv->text, prj, i, 0);
		argv = argv->next;
	}
	argv = prj->list_argv;
	prev = NULL;
	while (argv)
	{
		if (ft_strcmp(argv->text, "*") == 0 && argv->ex == 1)
		{
			new = make_more_argv(argv, prj->env_str);
			if (prev)
			{
				free_one_argv(argv);
				prev->next = new;
			}
			else
				prj->list_argv = new;
			argv = new->next;
		}
		prev = argv;
		argv = argv->next;
	}
}
