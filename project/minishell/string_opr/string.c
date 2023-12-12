/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 11:13:42 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static size_t	counter(char const *s, char c)
{
	size_t	counts;

	if (!s || !*s)
		return (0);
	counts = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			counts++;
		while (*s != c && *s)
			s++;
	}
	return (counts);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	lenss;
	int		i;

	str = (char **)malloc((counter(s, c) + 1) * sizeof(char *));
	if (!s || !str)
		exit(print_error(MALCERR));
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				lenss = ft_strlen(s);
			else
				lenss = ft_strchr(s, c) - s;
			str[i++] = ft_substr(s, 0, lenss);
			s += lenss;
		}
	}
	str[i] = NULL;
	return (str);
}

char	*ft_strdup(char *src, int size)
{
	char	*s;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	if (size > 0)
		i = size;
	else
		size = i;
	s = malloc((sizeof(char) * i) + 1);
	if (s == NULL)
		exit(print_error(MALCERR));
	i = 0;
	while (i < size)
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (*str1 || *str2)
	{
		if (n-- < 1)
			return (0);
		if (!*str1)
			return (-*str2);
		else if (!*str2)
			return (*str1);
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

char	*create_str(int size)
{
	char *str;

	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		exit(print_error(MALCERR));
	str[size] = '\0';
	return (str);
}
