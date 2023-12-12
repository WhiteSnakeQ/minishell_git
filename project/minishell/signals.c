/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 14:23:29 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <signal.h>

int	check_pid(int mod, t_prj **prj)
{
	static t_prj	*clean = NULL;

	if (mod == SET)
	{
		clean = *prj;
		return (0);
	}
	if (!clean)
		return (0);
	if (clean->pid == 0)
		return (0);
	kill(clean->pid, 15);
	clean->skip = 1;
	return (1);
}

void	signal_sig(int syg)
{
	(void)syg;
	if (check_pid(GET, NULL) == 1)
		return ;
	ft_printf(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_exit(int syg)
{
	(void)syg;
	clean_prj(GET, NULL);
	exit(0);
}

void	signal_quit(int syg)
{
	(void)syg;
	if (check_pid(GET, NULL) == 0)
		return ;
	ft_printf(2, CORE_D);
	return ;
}

void	set_signals(t_prj *prj)
{
	struct sigaction	act;

	check_pid(SET, &prj);
	act.sa_handler = signal_sig;
	if (sigaction(SIGINT, &act, NULL) == -1)
	{
		perror("minishell: signal operations");
		clean_prj(GET, NULL);
		exit(0);
	}	
	act.sa_handler = signal_quit;
	if (sigaction(SIGQUIT, &act, NULL) == -1)
	{
		perror("minishell: signal operations");
		clean_prj(GET, NULL);
		exit(0);
	}
}
