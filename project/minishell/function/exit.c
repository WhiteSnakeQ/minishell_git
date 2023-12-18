/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abobylev <abobylev@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:07:17 by abobylev          #+#    #+#             */
/*   Updated: 2023/12/17 21:07:19 by abobylev         ###   ########.fr       */
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
