/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 14:12:43 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static char	*get_path(char *str, char **paths)
{
	int		i;
	char	*cheack;
	char	*midl;

	i = 0;
	while (paths[i])
	{
		cheack = ft_strjoin(paths[i], "/");
		midl = ft_strjoin(cheack, str);
		free(cheack);
		cheack = midl;
		if (access(cheack, X_OK) == 0)
			return (cheack);
		free(cheack);
		i++;
	}
	return (NULL);
}

static t_argv	*init_text(char *text, int *i)
{
	t_argv	*cmd;
	int		size;

	size = 0;
	if (!text || !text[0])
	{
		*i += 1;
		return (NULL);
	}
	while (text[size] && ((text[size] < 9 || text[size] > 13) \
		&& text[size] != 32))
		size++;
	if (size == 0)
		return (NULL);
	cmd = malloc(sizeof(t_argv));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->name = NULL;
	cmd->text = ft_strdup(&text[0], size);
	*i += size;
	return (cmd);
}

static t_argv	*lstlast(t_argv *lst)
{
	t_argv		*my_list;

	my_list = lst;
	if (my_list == (void *)0)
		return (0);
	while (my_list->next)
		my_list = my_list->next;
	return (my_list);
}

void	parse_argv(t_prj *prj)
{
	t_argv	*cmd;
	int		i;

	i = 0;
	if (!prj->argv)
		return ;
	while ((prj->argv[i] >= 9 && prj->argv[i] <= 13) || prj->argv[i] == 32)
		i++;
	prj->list_argv = init_text(&prj->argv[i], &i);
	if (!prj->list_argv)
		return ;
	prj->list_argv->name = get_path(prj->list_argv->text, prj->paths);
	while (prj->argv[i])
	{
		while ((prj->argv[i] >= 9 && prj->argv[i] <= 13) || prj->argv[i] == 32)
			i++;
		cmd = init_text(&prj->argv[i], &i);
		if (!cmd)
			continue ;
		cmd->name = get_path(cmd->text, prj->paths);
		lstlast(prj->list_argv)->next = cmd;
	}
}
