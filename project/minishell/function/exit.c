/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit .c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 09:34:47 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	exit_nr(char **strs)
{
	ft_printf(2, "minishell: exit: ");
	ft_printf(2, "%s: ", strs[1]);
	ft_printf(2, "%s\n", NUMREC);
	clean_prj(GET, NULL);
	exit(2);
}

void	exit_m(char **strs, t_prj *prj)
{
	unsigned char	i;

	if (!strs)
		return ;
	if (strs[1])
	{
		if (ft_isdigit(strs[1]) == 1 && !strs[2])
		{
			i = (unsigned char)ft_atoi(strs[1]);
			clean_prj(GET, NULL);
			exit(i);
		}
		else if (ft_isdigit(strs[1]) == 1 && strs[2])
		{
			ft_printf(2, "%s\n", INVEXIT);
			prj->exit = 1;
			return ;
		}
		else
			exit_nr(strs);
	}
	clean_prj(GET, NULL);
	exit(0);
}
