/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/15 08:51:13 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_argv	*check_sp_smb(t_argv *argv, t_cmd *cmd, t_prj *prj)
{
	if (!argv)
		return (argv);
	if (ft_strcmp(argv->text, ">") == 0)
		change_fd_write(cmd, SINGLE, argv->next->text);
	else if (ft_strcmp(argv->text, ">>") == 0)
		change_fd_write(cmd, DOUBLE, argv->next->text);
	else if (ft_strcmp(argv->text, "<") == 0)
		change_fd_read(cmd, SINGLE, argv->next->text, prj);
	else if (ft_strcmp(argv->text, "<<") == 0)
		change_fd_read(cmd, DOUBLE, argv->next->text, prj);
	else
		return (argv);
	return (check_sp_smb(argv->next->next, cmd, prj));
}

static void	add_text(t_text **text, t_argv *argv)
{
	t_text	*new;
	t_text	*curr;

	new = malloc(sizeof(t_text));
	if (!new)
		exit(print_error(MALCERR));
	new->text = ft_strdup(argv->text, 0);
	new->next = NULL;
	if (!*text)
		*text = new;
	else
	{
		curr = *text;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

static char	**merge_text(t_text *text)
{
	char	**strs;
	t_text	*curr;
	int		i;

	curr = text;
	i = 0;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		exit(print_error(MALCERR));
	i = 0;
	while (text)
	{
		strs[i++] = ft_strdup(text->text, 0);
		text = text->next;
	}
	strs[i] = NULL;
	return (strs);
}

static t_argv	*create_cmd(t_argv *argv, t_prj *prj, int mod)
{
	t_cmd	*cmd;
	t_text	*text;

	cmd = init_cmd();
	cmd->valid = mod;
	text = NULL;
	while (argv)
	{
		argv = check_sp_smb(argv, cmd, prj);
		if (check_cmd(&argv) == -1)
			break ;
		add_text(&text, argv);
		argv = argv->next;
	}
	if (!text)
	{
		free(cmd);
		return (argv);
	}
	cmd->cmd_name = ft_strdup(text->text, 0);
	cmd->argv = merge_text(text);
	free_text(text);
	add_last_cmd(&prj->cmd, cmd);
	return (argv);
}

void	make_cmd(t_prj *prj, t_argv *argv, int mod)
{
	if (!argv)
		return ;
	if (check_sp_smb_arv(argv) == -1)
		return ;
	while (argv)
	{
		argv = create_cmd(argv, prj, mod);
		if (!argv)
			break ;
		if (ft_strcmp(argv->text, "||") == 0 && argv->ex == 1)
		{
			mod = 3;
			argv = argv->next;
		}
		if (!argv)
			break ;
		if (ft_strcmp(argv->text, "&&") == 0 && argv->ex == 1)
		{
			mod = 2;
			argv = argv->next;
		}
	}
	check_for_ex(prj);
}
