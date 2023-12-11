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

void	printf_all(t_prj *prj)
{
	t_argv	*cmd;

	cmd = prj->list_argv;
	while (cmd)
	{
		ft_printf(2, "argv -- %s\n", cmd->text);
		ft_printf(2, "name -- %s\n", cmd->name);
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_prj	*prj;

	(void)argv;
	set_signals();
	if (argc != 1)
		return (print_error(ERRARG));
	prj = malloc(sizeof(t_prj));
	if (!prj)
		return (print_error(MALCERR));
	clean_prj(SET, &prj);
	init_prj(prj, env);
	while (prj->exit != 1)
	{
		prj->argv = readline(NAME);
		parse_argv(prj);
		make_action(prj);
		clean_dirty(prj);
	}
	clean_prj(GET, NULL);
	return (0);
}
