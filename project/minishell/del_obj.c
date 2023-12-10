/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:14:32 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 01:23:06 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	clean(int mod, t_prj **prj)
{
	static t_prj	*to_clen = NULL;

	if (mod == SETPRJ)
	{
		to_clen = *prj;
		return ;
	}
	if (!to_clen)
		return ;
	free_string(to_clen->path);
	free(to_clen);
}
