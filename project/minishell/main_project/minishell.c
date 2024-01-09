/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2024/01/09 10:01:00 by kreys            ###   ########.fr       */
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
	clean_prj(SET, &prj);
	init_prj(prj, envs);
	while (42)
	{
		prj->argv = readline(NAME);
		add_history(prj->argv);
		prj->exit = 0;
		if (!prj->argv)
			exit(print_error("exit\n"));
		parse_argv(prj);
		execute_cmd(prj, prj->cmd, 0, 1);
		clean_dirty(prj);
	}
	return (0);
}
