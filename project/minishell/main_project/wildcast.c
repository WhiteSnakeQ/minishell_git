/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abobylev <abobylev@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 21:03:26 by abobylev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_argv	*make_argv(char *text)
{
	t_argv	*argv;

	if (!text)
		return (NULL);
	argv = malloc(sizeof(t_argv));
	argv->ex = 0;
	argv->next = NULL;
	text = del_symbl(text, "\n");
	argv->text = text;
	return (argv);
}

static void	make_ls(int *fd, char **env)
{
	char	*str[2];

	str[0] = "ls";
	str[1] = NULL;
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execve("/bin/ls", str, env);
}

static t_argv	*get_last_list(t_argv *argv)
{
	if (!argv)
		return (NULL);
	while (argv->next)
		argv = argv->next;
	return (argv);
}

static t_argv	*make_more_argv(char **env)
{
	t_argv		*prev;
	t_argv		*start;
	pid_t		pid;
	int			piper[2];
	t_helper	help;

	if (pipe(piper) == -1)
		exit (print_error(PIPERR));
	pid = fork();
	if (pid == -1)
		exit(print_error(PEDERR));
	if (pid == 0)
		make_ls(piper, env);
	waitpid(-1, &help.i, 0);
	close(piper[1]);
	help.str = get_next_line(piper[0]);
	prev = make_argv(help.str);
	start = prev;
	while (help.str)
	{
		help.str = get_next_line(piper[0]);
		prev->next = make_argv(help.str);
		prev = prev->next;
	}
	return (close(piper[0]), start);
}

void	make_wildcast(t_prj *prj, t_argv *argv)
{
	t_argv	*new;
	t_argv	*prev;

	prev = NULL;
	while (argv)
	{
		if (ft_strcmp(argv->text, "*") == 0 && argv->ex == 1)
		{
			new = make_more_argv(prj->env_str);
			if (prev)
				prev->next = new;
			else
				prj->list_argv = new;
			free_one_argv(argv);
			get_last_list(new)->next = argv->next;
			argv = new;
		}
		prev = argv;
		argv = argv->next;
	}
}
