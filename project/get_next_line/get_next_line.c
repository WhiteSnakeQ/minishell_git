/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:59:11 by kreys             #+#    #+#             */
/*   Updated: 2023/11/12 18:36:45 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_str(char	*str)
{
	int		size;
	int		i;
	char	*str_to_ret;

	size = 0;
	i = -1;
	while (str[size] && str[size] != '\n')
		size++;
	if (str[size] == '\n')
		size++;
	str_to_ret = malloc(sizeof(char) * (size + 1));
	if (!str_to_ret)
		return (NULL);
	while (++i < size)
		str_to_ret[i] = str[i];
	str_to_ret[i] = '\0';
	return (str_to_ret);
}

char	*read_file(char *full_str, int file)
{
	int		status_f;
	char	*string;

	string = malloc(sizeof(char) * ((long)BUFFER_SIZE + 1));
	if (!string)
	{
		free(string);
		return (NULL);
	}
	status_f = read(file, string, BUFFER_SIZE);
	if (status_f <= 0)
	{
		free(string);
		return (full_str);
	}
	string[status_f] = '\0';
	full_str = strjoins(full_str, string, 0, status_f);
	free(string);
	if (check_new_line(full_str) == 1)
		return (full_str);
	return (read_file(full_str, file));
}

char	*get_next_line(int fd)
{
	static char		*str[1025];
	char			*to_ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT32_MAX)
		return (NULL);
	if (read(fd, NULL, 0) == -1)
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	if (check_new_line(str[fd]) == 0)
		str[fd] = read_file(str[fd], fd);
	if (!str[fd])
		return (NULL);
	to_ret = read_str(str[fd]);
	str[fd] = clean_str(str[fd], 0);
	return (to_ret);
}
