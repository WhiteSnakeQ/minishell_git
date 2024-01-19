/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2024/01/19 17:10:20 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*add_to_start(char *str, char symb)
{
	int		i;
	int		j;
	char	*ret;

	j = -1;
	i = ft_strlen(str);
	ret = create_str(i + 1);
	ret[++j] = symb;
	while (str[++j - 1])
		ret[j] = str[j - 1];
	free_string(str);
	return (ret);
}

int	check_dollr(char *str, int i, t_prj *prj)
{
	if (str[i] == '$' && (!str[i + 1] || \
		symbl_in_str(" $\'\"=<>|0123456789", str[i + 1]) == 1))
	{
		return (1);
	}
	if (str[i] == '$' && str[i + 1] == '?')
		return (ft_strlen(prj->l_cmd));
	if (str[i] == '$' && str[i + 1] == ' ')
		return (1);
	return (0);
}

int	copy_to(t_helper *p, t_prj *prj, int *srt, char *ret)
{
	if (p->str[p->i] == '$' && (!p->str[p->i + 1] || \
		symbl_in_str(" $\'\"=<>|0123456789", p->str[p->i + 1]) == 1))
		return (ret[*srt] = '$', *srt += 1, 1);
	if (p->str[p->i] == '$' && p->str[p->i + 1] == '?')
		return (p->i = ft_strlcpy(&ret[*srt], prj->l_cmd, \
			ft_strlen(prj->l_cmd) + 1), *srt += p->i, 2);
	if (p->str[p->i] == '$' && p->str[p->i + 1] == ' ')
		return (ret[*srt] = '$', *srt += 1, 1);
	return (0);
}

int	check_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (symbl_in_str("}{^-+!./\\", str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	calc_tild(char *str, int *stop, t_prj *prj)
{
	int		to_ret;

	to_ret = 0;
	*stop += 1;
	if (!str[*stop] || str[*stop] == '/')
	{
		*stop += 1;
		to_ret += get_value_env_int("HOME", prj->env);
		if (str[*stop])
			to_ret += 1;
	}
	else
		to_ret = 1;
	return (to_ret);
}
