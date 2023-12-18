/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abobylev <abobylev@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:07:12 by abobylev          #+#    #+#             */
/*   Updated: 2023/12/17 21:07:15 by abobylev         ###   ########.fr       */
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
