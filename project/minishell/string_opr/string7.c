/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/15 14:02:22 by kreys            ###   ########.fr       */
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
	if (str[i] == '$' && (!str[i + 1] || str[i + 1] == '\"' \
		|| str[i + 1] == '$'))
		return (1);
	if (str[i] == '$' && str[i + 1] == '?')
		return (ft_strlen(prj->l_cmd));
	if (str[i] == '$' && str[i + 1] == ' ')
		return (1);
	return (0);
}

int	copy_to(t_helper *p, t_prj *prj, int *srt, char *ret)
{
	if (p->str[p->i] == '$' && (!p->str[p->i + 1] || p->str[p->i + 1] == '\"' \
		|| p->str[p->i + 1] == '$'))
		return (ret[*srt] = '$', *srt += 1, 1);
	if (p->str[p->i] == '$' && p->str[p->i + 1] == '?')
		return (p->i = ft_strlcpy(&ret[*srt], prj->l_cmd, \
			ft_strlen(prj->l_cmd) + 1), *srt += 2, p->i);
	if (p->str[p->i] == '$' && p->str[p->i] == ' ')
		return (ret[*srt] = '$', *srt += 1, 1);
	return (0);
}
