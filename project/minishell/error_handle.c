/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:07:51 by kreys             #+#    #+#             */
/*   Updated: 2023/12/15 08:41:09 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_error(t_prj *prj)
{
	prj->pid = 0;
	return (0);
}

int	print_error(char *message)
{
	printf("%s", message);
	clean_prj(GET, NULL);
	return (1);
}
