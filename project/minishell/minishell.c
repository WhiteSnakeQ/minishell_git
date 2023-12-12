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
	char	*strs[3];
	char	*exportt[3];
	char	*exp[3];

	exp[1] = NULL;
	strs[1] = "z";
	exportt[1] = "z";
	strs[2] = NULL;
	exportt[2] = NULL;
	if (argc != 1 || argv[1])
		return (print_error(ERRARG));
	prj = malloc(sizeof(t_prj));
	if (!prj)
		return (print_error(MALCERR));
	set_signals(prj, SET);
	clean_prj(SET, &prj);
	init_prj(prj, env);
	while (42)
	{
		set_signals(prj, GET);
		prj->argv = readline(NAME);
		if (!prj->argv)
			exit(print_error("exit\n"));
		export(exportt, prj);
		unset(strs, prj);
		export(exp, prj);
		set_signals(prj, GET);
		clean_dirty(prj);
	}
	return (0);
}
