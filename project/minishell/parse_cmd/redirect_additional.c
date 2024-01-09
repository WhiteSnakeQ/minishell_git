/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_additional.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2024/01/09 11:08:03 by kreys            ###   ########.fr       */
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
	while (str[i] && (str[i] != ' ' && str[i] != '$' && str[i] != '\'' \
			&& str[i] != '\"' && str[i] != '='))
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

static int	calc_s_q(char *str, int *stop)
{
	int	i;

	i = 0;
	while (str[i] != '\'')
		i++;
	return (*stop += i, i);
}

static int	check_doubl_q(char *str, t_prj *prj, int i)
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
		}
		else if (str[i] == '\'' && i++ > -1)
		{
			size += calc_s_q(&str[i], &i);
			if (str[i])
				i++;
		}
		else if (str[i] == '$' && prj->skip_dollar == 0)
			size += calc_g_env(&str[i], prj, &i, 0);
		else if (str[i] && i++ > -1)
			size++;
	}
	return (size);
}

char	*convert_to_normal(char *str, t_prj *prj, char *stop)
{
	int	i;
	int	deff;

	if (!str || scan(stop, str) == 0)
		return (NULL);
	deff = prj->skip_dollar;
	prj->skip_dollar = 0;
	str = del_symbl(str, "\n");
	i = check_doubl_q(str, prj, 0);
	str = make_full(str, prj, i, 0);
	str = ft_strjoin(str, "\n");
	prj->skip_dollar = deff;
	return (str);
}
