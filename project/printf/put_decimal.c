/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_decimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:37:03 by kreys             #+#    #+#             */
/*   Updated: 2023/11/04 20:19:31 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project_f.h"

void	put_nbr(int digit, t_action **act)
{
	long	digit2;

	digit2 = digit;
	if (digit < 0)
	{
		(*act)->txt[(*act)->pos++] = '-';
		digit2 = -digit2;
	}
	if (digit2 > 9)
	{
		put_nbr(digit2 / 10, act);
		(*act)->txt[(*act)->pos++] = (digit2 % 10) + '0';
		return ;
	}
	(*act)->txt[(*act)->pos++] = digit2 + '0';
}

void	put_decimal(int digit, t_action **act)
{
	int	size;

	size = get_decimal_size(digit);
	(*act)->txt = malloc(sizeof(char) * (size + 1));
	if (!(*act)->txt)
		return ;
	(*act)->s_txt += size;
	(*act)->txt[size] = '\0';
	put_nbr(digit, act);
	(*act)->act = 'd';
}
