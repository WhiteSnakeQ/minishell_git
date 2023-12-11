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
}

void	set_signals(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = NULL;
	signal(SIGINT, signal_sig);
	signal(SIGQUIT, signal_exit);
	sigaction()
}
