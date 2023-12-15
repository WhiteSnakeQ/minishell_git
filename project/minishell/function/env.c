/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/15 11:25:32 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	env(char **strs, t_prj *prj, int fd)
{
	if (!strs)
		exit(0);
	print_strings(prj->env_str, NL, fd);
	prj->exit = 0;
	return ;
}
