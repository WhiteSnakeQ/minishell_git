/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_act.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:42:24 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 14:11:57 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	cl_cmd_one(t_prj *prj)
{
	t_argv	*clean;

	clean = prj->list_argv;
	prj->list_argv = prj->list_argv->next;
	free_string(clean->name);
	free_string(clean->text);
}

char	**make_exec(t_prj *prj)
{
	t_argv	*argv;
	char	**ex;
	int		size;
	int		i;

	size = 1;
	i = 0;
	argv = prj->list_argv->next;
	while (argv && !argv->name)
	{
		size++;
		argv = argv->next;
	}
	argv = prj->list_argv;
	ex = malloc(sizeof(char *) * (size + 1));
	ex[size] = NULL;
	while (i < size)
	{
		ex[i++] = ft_strdup(argv->text, 0);
		cl_cmd_one(prj);
		argv = prj->list_argv;
	}
	return (ex);
}

void	execute(t_prj *prj, char **ex, char *name)
{
	int	close;

	ft_printf(2, name);
	prj->pid = fork();
	if (prj->pid == 0)
	{
		execve(name, ex, prj->env);
		exit(1);
	}
	else
	{
		waitpid(-1, &close, 0);
		free_strings(ex);
		free_string(name);
		return ;
	}
}

void	make_action(t_prj *prj)
{
	t_argv	*argv;
	int		action;
	char	**exec;
	char	*name;

	action = 0;
	argv = prj->list_argv;
	while (argv && action != 1)
	{
		if (argv->name)
		{
			name = ft_strdup(argv->name, 0);
			exec = make_exec(prj);
			execute(prj, exec, name);
			argv = prj->list_argv;
		}
		else
		{
			ft_printf(2, "%s%s\n", FILNF, argv->text);
			exit(print_error("finisha"));
		}
	}
}
