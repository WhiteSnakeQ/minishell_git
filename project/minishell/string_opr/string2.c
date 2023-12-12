/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:41:31 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 09:15:46 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		exit(print_error(MALCERR));
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

void	free_strings(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

char	*ft_strchr(const char *src, int symbol)
{
	while (*src)
	{
		if (*src)
			if (*src == (char)symbol)
				return ((char *)src);
		src++;
	}
	if (symbol == '\0')
		return ((char *)src);
	return (0);
}

int	ft_strlen(const char *str)
{
	int		size;

	size = 0;
	if (!str)
		return (0);
	while (str[size])
		size++;
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*src;
	size_t			size;
	size_t			i;

	i = 0;
	size = 0;
	if (s == NULL)
		return (NULL);
	src = malloc(sizeof(*s) * (len + 1));
	if (src == NULL)
		exit(print_error(MALCERR));
	while (len > size && s[i])
	{
		if (i >= start)
			src[size++] = s[i];
		i++;
	}
	src[size] = 0;
	return (src);
}
