/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 09:13:01 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_sp(char *str)
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

static void	helper_crt(char *str, char *finish, int i)
{
	int		act;

	act = 0;
	if (*finish == str[i] && act++ > -1)
		*finish = '\0';
	if (*finish == '\0' && str[i] == '\'' && act == 0)
		*finish = '\'';
	if (*finish == '\0' && str[i] == '\"' && act == 0)
		*finish = '\"';
}

static char	*create_one_arg(char *s, int *skip)
{
	t_helper	h;

	h.i = -1;
	h.ch = '\0';
	while (++h.i > -2 && s[h.i])
	{
		if ((s[h.i] == '<' || s[h.i] == '>' || s[h.i] == '|' || \
			(s[h.i] == '&' && s[h.i + 1] == '&')) && h.i == 0)
		{
			h.i += check_sp(s);
			break ;
		}
		helper_crt(s, &h.ch, h.i);
		if (((s[h.i] == '<' || s[h.i] == '>' || s[h.i] == '|' || (s[h.i] == '&' \
				&& s[h.i + 1] == '&')) && h.ch == '\0') || (((s[h.i] >= 9 && \
					s[h.i] <= 13) || s[h.i] == 32) && h.ch == '\0'))
			break ;
	}
	h.str = ft_strdup(s, h.i);
	if (h.ch != '\0')
		h.str = add_to_end(h.str, h.ch);
	*skip += h.i;
	return (h.str);
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
	int			i;
	char		*str;

	i = 0;
	if (!prj->argv)
		return ;
	while ((prj->argv[i] >= 9 && prj->argv[i] <= 13) || prj->argv[i] == ' ')
		i++;
	while (prj->argv[i])
	{
		str = create_one_arg(&prj->argv[i], &i);
		add_back_argv(prj, str);
		while ((prj->argv[i] >= 9 && prj->argv[i] <= 13) || prj->argv[i] == ' ')
			i++;
	}
	parse_quotet(prj);
	make_cmd(prj, prj->list_argv, 1);
}
