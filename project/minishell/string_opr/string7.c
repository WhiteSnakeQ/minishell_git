/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/15 01:05:36 by codespace        ###   ########.fr       */
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
