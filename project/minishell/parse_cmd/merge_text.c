/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:28:45 by codespace         #+#    #+#             */
/*   Updated: 2024/01/19 16:41:53 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	calc_g_env(char *str, t_prj *prj, int *srt, char *ret)
{
	t_helper	p;

	p.i = 0;
	p.str = str;
	p.j = copy_to(&p, prj, srt, ret);
	if (p.j != 0)
		return (p.j);
	p.j = 1;
	p.i++;
	while (str[p.i] && symbl_in_str(" $\'\"=<>|", str[p.i]) == 0)
	{
		if ((str[p.i] >= '0' && str[p.i] <= '9') && p.i == 0)
			return (1);
		p.i++;
	}
	if (p.i == 1 && prj->parsing == 0)
		return (p.i);
	p.str = ft_strdup(&str[p.j], p.i - (p.j));
	p.j = ft_strlcpy(&ret[*srt], get_value_env_str(p.str, prj->env), \
		ft_strlen(get_value_env_str(p.str, prj->env)) + 1);
	return (*srt += p.j, free_string(p.str), p.i);
}

static int	calc_d_q(char *str, t_prj *prj, int *start, char *ret)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i] != '\"')
	{
		if (str[i] == '$')
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
		*i += 1;
		*i += calc_d_q(&str[*i], prj, &help->j, help->str);
		if (str[*i] == '\"')
			*i += 1;
	}
	else if (str[*i] == '\'')
	{
		*i += 1;
		*i += calc_s_q(&str[*i], &help->j, help->str);
		if (str[*i])
			*i += 1;
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
		if ((str[i] == '\"' || str[i] == '\''))
			helper_q(&i, str, prj, &help);
		else if (str[i] == '$' && prj->skip_dollar == 0)
		{
			help.str[help.j] = '\0';
			prj->parsing = 0;
			i += calc_g_env(&str[i], prj, &help.j, help.str);
		}
		else if (str[i] && str[i] == '~')
			i += make_tild(&str[i], prj, &help.j, help.str);
		else if (str[i] && str[i] != '\"')
			help.str[help.j++] = str[i++];
	}
	free_string(str);
	return (help.str);
}
