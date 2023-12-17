/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 01:35:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	main(int argc, char **argv, char **envs)
{
	t_prj	*prj;

	if (argc != 1 || argv[1])
		return (print_error(ERRARG));
	prj = malloc(sizeof(t_prj));
	if (!prj)
		return (print_error(MALCERR));
	set_signals(prj, SET);
	clean_prj(SET, &prj);
	init_prj(prj, envs);
	while (42)
	{
		set_signals(prj, GET);
		prj->argv = readline(NAME);
		add_history(prj->argv);
		if (!prj->argv)
			exit(print_error("exit\n"));
		parse_argv(prj);
		set_signals(prj, GET);
		execute_cmd(prj, prj->cmd, 0, 0);
		clean_dirty(prj);
	}
	return (0);
}
