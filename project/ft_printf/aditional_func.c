/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aditional_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:42:55 by kreys             #+#    #+#             */
/*   Updated: 2023/11/04 20:19:44 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project_f.h"

void	initialize(t_action **act)
{
	(*act)->txt = NULL;
	(*act)->act = '\0';
	(*act)->pos = 0;
	(*act)->skip = 0;
	(*act)->padding_left = 0;
	(*act)->zero = 0;
	(*act)->plus = 0;
	(*act)->space = 0;
	(*act)->point = 0;
	(*act)->sharp = 0;
	(*act)->width = 0;
	(*act)->s_txt = 0;
	(*act)->use = 0;
	(*act)->s_pad = 0;
	(*act)->s_pnt = 0;
	(*act)->count = 0;
}

int	calculate_size(unsigned long long digit)
{
	int		i;

	i = 1;
	while (digit > 16)
	{
		digit /= 16;
		i++;
	}
	return (i);
}

int	get_u_decimal_size(unsigned int digit)
{
	int		size;

	size = 1;
	while (digit > 9)
	{
		digit /= 10;
		size++;
	}
	return (size);
}

int	get_decimal_size(int digit)
{
	int		size;
	long	digit2;

	size = 1;
	digit2 = digit;
	if (digit < 0)
	{
		digit2 = -digit2;
		size++;
	}
	while (digit2 > 9)
	{
		digit2 /= 10;
		size++;
	}
	return (size);
}

void	put_hex(unsigned long long digit, t_action **act, char *convert)
{
	if (digit > 16)
	{
		put_hex(digit / 16, act, convert);
		(*act)->txt[(*act)->pos++] = convert[digit % 16];
		return ;
	}
	if (digit == 16)
		(*act)->txt[(*act)->pos++] = convert[digit % 16];
}
