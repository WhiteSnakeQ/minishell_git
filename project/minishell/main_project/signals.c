/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2024/01/19 17:10:26 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_pid(int mod, t_prj **prj)
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
	{
		ft_printf(1, "\n");
		return ;
	}
	ft_printf(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_quit(int syg)
{
	(void)syg;
	if (check_pid(GET, NULL) == 0)
		return ;
	ft_printf(2, CORE_D);
	return ;
}

static void	set_signals_action(void)
{
	static int			i = 0;

	signal(SIGINT, SIG_IGN);
	if (i++ % 2 == 0)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_sig);
}

void	set_signals(t_prj *prj, int mod)
{
	if (mod == GET)
	{
		set_signals_action();
		return ;
	}
	check_pid(SET, &prj);
}
