/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:21:42 by codespace         #+#    #+#             */
/*   Updated: 2024/01/19 17:05:01 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	calc_g_env(char *str, t_prj *prj, int *stop, int i)
{
	int		j;
	char	*key;

	j = check_dollr(str, i, prj);
	if (j != 0 || i++ < -10)
	{
		if (str[1] == '?')
			(*stop)++;
		return ((*stop)++, j);
	}
	while (str[i] && symbl_in_str(" $\'\"=<>|", str[i]) == 0)
	{
		if ((str[i + 1] >= '0' && str[i + 1] <= '9') && i == 0)
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

static int	calc_d_q(char *str, t_prj *prj, int *stop, t_argv *argv)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	argv->ex = 0;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$' && prj->skip_dollar == 0)
			size += calc_g_env(&str[i], prj, &i, 0);
		else
		{
			i++;
			size++;
		}
	}
	return (*stop += i, size);
}

static int	calc_s_q(char *str, int *stop, t_argv *argv)
{
	int	i;

	i = 0;
	argv->ex = 0;
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
			size += calc_d_q(&str[i], prj, &i, argv);
			if (str[i])
				i++;
		}
		else if (str[i] == '\'' && i++ > -1)
		{
			size += calc_s_q(&str[i], &i, argv);
			if (str[i])
				i++;
		}
		else if (str[i] == '$' && prj->skip_dollar == 0)
			size += calc_g_env(&str[i], prj, &i, 0);
		else if (str[i] == '~')
			size += calc_tild(&str[i], &i, prj);
		else if (str[i] && i++ > -1)
			size++;
	}
	return (size);
}

void	parse_quotet(t_prj *prj)
{
	t_argv		*argv;
	int			i;
	int			skip_dollar_finish;

	skip_dollar_finish = 0;
	prj->skip_dollar = 0;
	argv = prj->list_argv;
	while (argv)
	{
		if (prj->skip_dollar == 1)
			skip_dollar_finish = 1;
		argv->ex = 1;
		if (ft_strcmp(argv->text, ">>") == 0 \
			|| ft_strcmp(argv->text, "<<") == 0 \
			|| ft_strcmp(argv->text, ">") == 0 \
			|| ft_strcmp(argv->text, "<") == 0)
			prj->skip_dollar = 1;
		i = check_doubl_q(argv->text, prj, argv, 0);
		argv->text = make_full(argv->text, prj, i, 0);
		if (skip_dollar_finish == 1 && skip_dollar_finish-- > -9)
			prj->skip_dollar = 0;
		argv = argv->next;
	}
	argv = prj->list_argv;
	make_wildcast(prj, argv);
}
