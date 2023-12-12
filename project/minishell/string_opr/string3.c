/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 14:19:20 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	int				size;

	size = 0;
	str = (unsigned char *)b;
	while (len-- > 0)
		str[size++] = c;
	return (b);
}

char	*new_str_till(char *env, char symbl)
{
	int 	i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	while (env[i] && env[i] != symbl)
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		exit(print_error(MALCERR));
	str[i] = '\0';
	while (j < i)
	{
		str[j] = env[j];
		j++;
	}
	return (str);
}

char	*new_str_after(char *env, char symbl)
{
	int 	i;
	int		j;
	int		start;
	char	*str;

	j = 0;
	i = 0;
	start = 0;
	while (env[start] && env[start] != symbl)
		start++;
	if (!env[start])
		return (NULL);
	start++;
	while (env[start + i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		exit(print_error(MALCERR));
	str[i] = '\0';
	while (j - 1 < i)
		str[j++] = env[start++];
	return (str);
}

char    *create_one_env(t_env *env)
{
    char    *str;
    int     size;
    int     i;
	int		j;

    i = 0;
	j = 0;
	size = 0;
	if (env->value)
		size = 1;
    size += ft_strlen(env->key);
	size += ft_strlen(env->value);
    str = create_str(size);
	while (env->key[j])
		str[i++] = env->key[j++];
	if (!env->value)
		return (str);
	str[i++] = '=';
	j = 0;
	while (env->value && env->value[j])
		str[i++] = env->value[j++];
	return (str);
}

void	free_string(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}
