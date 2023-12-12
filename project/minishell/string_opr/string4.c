/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 14:21:37 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void    print_strings(char **strs, int modprnt, int mod)
{
    int		i;

	i = 0;
	while (strs[i])
	{
		if (modprnt == NL)
			ft_printf(1, "%s\n", strs[i++]);
		else
			ft_printf(1, strs[i++]);
	}
    if (mod == CLEAN)
		free_strings(strs);
}

static int	cmp_one(char *str, char symb)
{
	int	size_s;

	size_s = 0;
	while (str[size_s])
	{
		if (str[size_s] == symb)
			return (-1) ;
		size_s++;
	}
	return (1);
}

static int	calc_size_del(char *str, char *symbl)
{
	int	size;
	int	real_size;

	size = -1;
	real_size = 0;
	if (!str)
		return (0);
	while (str[++size])
	{
		if (cmp_one(symbl, str[size]) == 1)
			real_size++;
	}
	return (real_size);
}

char	*del_symbl(char *str, char *symbl)
{
	int		size;
	int		i;
	char*	new_str;

	if (!str)
		return (NULL);
	i = -1;
	size = calc_size_del(str, symbl);
	new_str = create_str(size);
	size = 0;
	while (str[++i])
	{
		if (cmp_one(symbl, str[i]) == 1)
			new_str[size++] = str[i];
	}
	free_string(str);
	return (new_str);
}

char	*cover_char(char *str, char symb)
{
	char	*new_str;
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(str);
	new_str = create_str(size + 2);
	new_str[0] = symb;
	new_str[size + 1] = symb;
	while (str[i])
	{
		new_str[i + 1] = str[i];
		i++;
	}
	free_string(str);
	return (new_str);
}