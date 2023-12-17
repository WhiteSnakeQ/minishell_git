/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/16 17:40:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	clean_dirty(t_prj *prj)
{
	prj->pid = 0;
	free_argv(prj->list_argv);
	prj->list_argv = NULL;
	free_string(prj->argv);
	prj->argv = NULL;
	free_cmd(prj->cmd);
	prj->cmd = NULL;
}

void	clean_prj(int mod, t_prj **prj)
{
	static t_prj	*to_clean = NULL;

	if (mod == SET)
	{
		to_clean = *prj;
		return ;
	}
	if (!to_clean)
		return ;
	free_string(to_clean->name);
	free_string(to_clean->our_path);
	free_string(to_clean->argv);
	free_string(to_clean->l_cmd);
	free_strings(to_clean->paths);
	free_strings(to_clean->env_str);
	free_cmd(to_clean->cmd);
	free_argv(to_clean->list_argv);
	free_env(to_clean->env);
	if (to_clean->pipeold)
		free(to_clean->pipeold);
	free(to_clean);
	close(0);
	close(1);
	close(2);
}
