/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   start.c											:+:		:+:	:+:   */
/*													+:+ +:+			+:+	 */
/*   By: codespace <codespace@student.42.fr>		+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2023/12/11 00:14:32 by kreys				#+#	#+#			 */
/*   Updated: 2023/12/14 22:09:43 by codespace		###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "../headers/minishell.h"

static t_argv	*make_argv(char *text)
{
	t_argv	*argv;

	if (!text)
		return(NULL);
	argv = malloc(sizeof(t_argv));
	argv->ex = 0;
	argv->next = NULL;
	text = del_symbl(text, "\n");
	argv->text = text;
}

static void	make_ls(int *fd, char **env)
{
	char	*str[2];

	str[0] = "ls";
	str[1]= NULL;
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execve("/bin/ls", str, env);
}

t_argv	*make_more_argv(t_argv *argv, char **env)
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
	if (prev)
		prev->next = argv->next;
	close(piper[0]);
	return (start);
}
