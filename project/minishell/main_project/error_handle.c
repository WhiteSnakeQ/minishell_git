/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:07:51 by kreys             #+#    #+#             */
/*   Updated: 2023/12/16 17:40:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_signal_ignore(void)
{
	static int	i = 0;

	if (++i % 2 == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, signal_quit);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}

int	print_error(char *message)
{
	printf("%s", message);
	clean_prj(GET, NULL);
	return (1);
}
