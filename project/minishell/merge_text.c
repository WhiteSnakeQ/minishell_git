/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:28:45 by codespace         #+#    #+#             */
/*   Updated: 2023/12/14 22:41:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	calc_g_env(char *str, t_prj *prj, int *start, char *ret)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = -1;
	if (str[i] == '$')
	{
		ret[*start] = str[i];
		*start += 1;
		return (1);
	}
	if (str[i] == '?')
	{
		i = ft_strlcpy(&ret[*start], prj->last_cmd, ft_strlen(prj->last_cmd)
				+ 1);
		*start += 1;
		return (i);
	}
	while (str[i] && (str[i] != ' ' && str[i] != '$' && str[i] != '\''
			&& str[i] != '\"'))
	{
		if ((str[i] >= '0' && str[i] <= '9') && i == 0)
			return (1);
		i++;
	}
	if (i == 0 && prj->parsing == 0)
		return (i);
	else if (i == 0 && prj->parsing == 1)
		return (i);
	key = create_str(i);
	while (++j < i)
		key[j] = str[j];
	j = ft_strlcpy(&ret[*start], get_value_env_str(key, prj->env),
			ft_strlen(get_value_env_str(key, prj->env)) + 1);
	*start += j;
	free_string(key);
	return (i);
}

static int	calc_d_q(char *str, t_prj *prj, int *start, char *ret)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i] != '\"')
	{
		if (str[i] == '$' && i++ > -1)
		{
			prj->parsing = 1;
			i += calc_g_env(&str[i], prj, start, &ret[size]);
		}
		else
			ret[(*start)++] = str[i++];
	}
	return (i);
}

static int	calc_s_q(char *str, int *start, char *ret)
{
	int	i;

	i = 0;
	while (str[i] != '\'')
	{
		ret[*start] = str[i++];
		*start += 1;
	}
	return (i);
}

static void	helper_q(int *i, char *str, t_prj *prj, t_helper *help)
{
	if (str[*i] == '\"')
	{
		*i += calc_d_q(&str[*i], prj, &help->j, help->str);
		if (str[*i])
			*i += 1;
	}
	else if (str[*i] == '\'')
	{
		i += calc_s_q(&str[*i], &help->j, help->str);
		if (str[*i])
			i++;
	}
}

char	*make_full(char *str, t_prj *prj, int m_size, int i)
{
	t_helper	help;

	help.j = 0;
	help.str = create_str(m_size);
	help.c = ft_strlen(str);
	while (i < help.c)
	{
		if ((str[i] == '\"' || str[i] == '\'') && i++ > -1)
			helper_q(&i, str, prj, &help);
		else if (str[i] == '$' && i++ > -1)
		{
			help.str[help.j] = '\0';
			prj->parsing = 0;
			i += calc_g_env(&str[i], prj, &help.j, help.str);
		}
		else
			help.str[help.j++] = str[i++];
	}
	free_string(str);
	return (help.str);
}
