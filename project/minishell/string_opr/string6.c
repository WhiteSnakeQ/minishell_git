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

int symbl_in_str(char *str, char symb)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == symb)
            return (1);
        i++;
    }
    return (0);    
}

char    *add_to_end(char *str, char symb)
{
    int     i;
    int     j;
    char    *ret;

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
