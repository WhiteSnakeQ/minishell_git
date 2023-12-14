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

static int check_sp(char *str)
{
	if (str[0] == '|' && str[1] && str[0] == str[1])
		return (2);
	else if (str[0] == '|')
		return (1);
	else if (str[0] == '<' && str[1] && str[0] == str[1])
		return (2);
	else if (str[0] == '>' && str[1] && str[0] == str[1])
		return (2);
	else if (str[0] == '>')
		return (1);
	else if (str[0] == '<')
		return (1);
	else if (str[0] == '&' && str[1] && str[0] == str[1])
		return (2);
	return (0);
}

static char	*create_one_arg(char *str, int *skip)
{
	int		i;
	char	finish;
	char	*ret;

	i = 0;
	finish = '\0';
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>' || str[i] == '|' || (str[i] == '&' && str[i + 1] == '&')) && i == 0)
		{
			i += check_sp(str);
			break ;
		}
		if (finish == str[i] && i++ > -1)
			finish = '\0';
		if (finish == '\0' && str[i] == '\'')
			finish = '\'';
		if (finish == '\0' && str[i] == '\"')
			finish = '\"';
		if (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && finish == '\0')
			break ;
		if ((str[i] == '<' || str[i] == '>' || str[i] == '|' || (str[i] == '&' && str[i + 1] == '&')) && finish == '\0')
			break ;
		if (str[i])
			i++;
	}
	ret = ft_strdup(str, i);
	if (finish != '\0')
		ret = add_to_end(ret, finish);
	*skip += i;
	return (ret);
}

static void	add_back_argv(t_prj *prj, char *text)
{
	t_argv	*argv;
	t_argv	*curr;

	argv = malloc(sizeof(t_argv));
	if (!argv)
		exit(print_error(MALCERR));
	argv->next = NULL;
	argv->text = text;
	if (!prj->list_argv)
		prj->list_argv = argv;
	else
	{
		curr = prj->list_argv;
		while (curr->next)
			curr = curr->next;
		curr->next = argv;
	}
}

void	parse_argv(t_prj *prj)
{
	int		i;
	char	*str;

	i = 0;
	if (!prj->argv)
		return ;
	while ((prj->argv[i] >= 9 &&prj->argv[i] <= 13) || prj->argv[i] == ' ')
		i++;
	while (prj->argv[i])
	{
		str = create_one_arg(&prj->argv[i], &i);
		add_back_argv(prj, str);
		while ((prj->argv[i] >= 9 && prj->argv[i] <= 13) || prj->argv[i] == ' ')
			i++;
	}
}
