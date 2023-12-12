/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 14:10:12 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_prj	*prj;
	char	*exit_l[4];

	exit_l[1] = "56";
	exit_l[2] = "lol";
	exit_l[3] = NULL;
	if (argc != 1 || argv[1])
		return (print_error(ERRARG));
	prj = malloc(sizeof(t_prj));
	if (!prj)
		return (print_error(MALCERR));
	set_signals(prj);
	clean_prj(SET, &prj);
	init_prj(prj, env);
	while (42)
	{
		prj->argv = readline(NAME);
		if (!prj->argv)
			exit(print_error("exit\n"));
		clean_dirty(prj);
	}
	return (0);
}