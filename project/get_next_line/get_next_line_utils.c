/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:07:43 by kreys             #+#    #+#             */
/*   Updated: 2023/11/08 20:23:15 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_new_line(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i++] == '\n')
			return (1);
	}
	return (0);
}

int	strlens(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*strjoins(char *s1, char *s2, int size1, int size2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = -1;
	if (s1)
		size1 = strlens(s1);
	if (s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (size1 + size2 + 1));
	if (str == NULL)
		return (NULL);
	while (s1 && s1[++i] != '\0')
		str[i] = s1[i];
	if (i < 0)
		i = 0;
	while (j < size2 && s2[++j] != '\0')
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*clean_str(char *str, int i)
{
	char	*str_to_ret;
	int		size;
	int		start;

	size = strlens(str);
	start = 0;
	while (str[start] != '\0' && str[start] != '\n')
		start++;
	if (str[start] == '\n')
		start++;
	str_to_ret = malloc(sizeof(char) * (size - start + 1));
	if (!str_to_ret)
		return (NULL);
	str_to_ret[size - start] = '\0';
	while (str[start])
		str_to_ret[i++] = str[start++];
	free(str);
	if (!str_to_ret[0])
	{
		free(str_to_ret);
		return (NULL);
	}
	return (str_to_ret);
}
