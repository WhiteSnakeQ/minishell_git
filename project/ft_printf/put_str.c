/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:02:11 by kreys             #+#    #+#             */
/*   Updated: 2023/11/04 20:25:17 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project_f.h"

char	*str_dup(char *src)
{
	char	*s;
	int		i;

	i = 0;
	while (src[i])
		i++;
	s = malloc((sizeof(char) * i) + 1);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	str_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	put_str(char *str, t_action **act)
{
	if (str)
		(*act)->txt = str_dup(str);
	else
	{
		(*act)->txt = malloc(sizeof(char) * 7);
		(*act)->txt[0] = '(';
		(*act)->txt[1] = 'n';
		(*act)->txt[2] = 'u';
		(*act)->txt[3] = 'l';
		(*act)->txt[4] = 'l';
		(*act)->txt[5] = ')';
		(*act)->txt[6] = '\0';
	}
	(*act)->s_txt = str_len((*act)->txt);
	(*act)->act = 's';
}
