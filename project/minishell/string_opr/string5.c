/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 14:19:20 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (*(s1 + i) && *(s1 + i) == *(s2 + i))
		i++;
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}

int	calc_size_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (0);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[0] == '-')
		i++;
	while (str[i] && '0' <= str[i] && str[i] <= '9')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

static int	check_string(long long *number_print, \
	const char *symbol, int *minus)
{
	int	stop_cheking;

	stop_cheking = 0;
	if ((symbol[0] == '+' || symbol[0] == '-') && *number_print == 0)
	{
		stop_cheking++;
		if (symbol[0] == '-')
			*minus = -*minus;
		symbol++;
	}
	while (*symbol)
	{
		if (symbol[0] >= '0' && symbol[0] <= '9')
		{
			*number_print *= 10;
			*number_print += symbol[0] - 48;
			stop_cheking++;
		}
		else if (*number_print > 0)
			return (1);
		else
			return (-1);
		symbol++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	number_to_print;
	int			minus;

	minus = 1;
	number_to_print = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	check_string(&number_to_print, str, &minus);
	if ((number_to_print < 0 && number_to_print >= -9223372036854775807) \
		|| ft_strcmp(str, "9223372036854775808") == 0)
	{
		ft_printf(2, "minishell: exit: %s: %s\n", str, NUMREC);
		clean_prj(GET, NULL);
		exit(2);
	}
	if (minus == -1)
		number_to_print = -number_to_print;
	return ((int)number_to_print);
}
