/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_u_decimall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:49:33 by kreys             #+#    #+#             */
/*   Updated: 2023/11/04 20:19:23 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project_f.h"

void	put_u_nbr(unsigned int digit, t_action **act)
{
	if (digit > 9)
	{
		put_u_nbr(digit / 10, act);
		(*act)->txt[(*act)->pos++] = (digit % 10) + '0';
		return ;
	}
	(*act)->txt[(*act)->pos++] = digit + '0';
}

void	put_u_decimal(unsigned int digit, t_action **act)
{
	int	size;

	size = get_u_decimal_size(digit);
	(*act)->txt = malloc(sizeof(char) * (size + 1));
	if (!(*act)->txt)
		return ;
	(*act)->s_txt += size;
	(*act)->txt[size] = '\0';
	put_u_nbr(digit, act);
	(*act)->act = 'u';
}
