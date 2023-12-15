/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 12:46:32 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	symbl_in_str(char *str, char symb)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == symb)
			return (1);
		i++;
	}
	return (0);
}

char	*add_to_end(char *str, char symb)
{
	int		i;
	int		j;
	char	*ret;

	j = -1;
	i = ft_strlen(str);
	ret = create_str(i + 1);
	ret[i] = symb;
	while (str[++j])
		ret[j] = str[j];
	free_string(str);
	return (ret);
}

int	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	count;

	count = 0;
	while (size != 1 && size > 0 && *src)
	{
		size--;
		*dest = *src;
		dest++;
		src++;
		count++;
	}
	if (size <= 0)
		return (count);
	return (count);
}

static size_t	get_digits(long n, int minus)
{
	size_t	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	if (minus == 1)
		return ((size_t)(i + 1));
	return ((size_t)i);
}

char	*ft_itoa(int n, char *clean)
{
	char		*str_num;
	size_t		digits;
	int			minus;
	long int	num;

	free_string(clean);
	minus = 0;
	num = n;
	if (n < 0 && minus++ == 0)
		num = -num;
	digits = get_digits(num, minus);
	str_num = malloc(sizeof(char) * (digits + 1));
	if (str_num == NULL)
		return (NULL);
	str_num[digits--] = '\0';
	while (num > 9)
	{
		str_num[digits--] = num % 10 + '0';
		num /= 10;
	}
	str_num[digits--] = num + '0';
	if (minus)
		str_num[digits--] = '-';
	return (str_num);
}
