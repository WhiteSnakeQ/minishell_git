/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 02:38:23 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_prj	*prj;
	char	*str;

	(void)av;
	(void)env;
	if (ac != 1)
		return (print_error(ERRARG));
	prj = malloc(sizeof(t_prj));
	if (!prj)
		return (print_error(MALCERR));
	clean(SETPRJ, &prj);
	init_prj(prj);
	str = readline(NAME);
	ft_printf(1, "%s", str);
	return (0);
}
