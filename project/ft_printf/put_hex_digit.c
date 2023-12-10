/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex_digit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:51:21 by kreys             #+#    #+#             */
/*   Updated: 2023/11/04 20:19:28 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project_f.h"

void	put_hex_sp(unsigned long long digit, t_action **act, char *convert)
{
	if (digit > 16)
	{
		put_hex_sp(digit / 16, act, convert);
		(*act)->txt[(*act)->pos++] = convert[digit % 16];
	}
	else
	{
		if (digit == 16)
			(*act)->txt[(*act)->pos++] = convert[digit / 16];
		(*act)->txt[(*act)->pos++] = convert[digit % 16];
	}
}

int	check_for_hex(unsigned long long digit)
{
	if (digit == 0)
		return (0);
	while (digit > 16)
		digit /= 16;
	if (digit % 16 == 0)
		return (1);
	return (0);
}

void	put_hex_digit(unsigned int hex, t_action **act, int mod)
{
	int		size;

	size = calculate_size((unsigned long long)hex);
	if (check_for_hex((unsigned long long)hex) == 1)
		size += 1;
	if ((*act)->sharp == 1 && (unsigned long long)hex != 0)
		size += 2;
	(*act)->txt = malloc (sizeof(char) * (size + 1));
	(*act)->txt[size] = '\0';
	if ((*act)->sharp == 1 && (unsigned long long)hex != 0)
	{
		(*act)->txt[0] = '0';
		if (mod == 1)
			(*act)->txt[1] = 'X';
		else if (mod == 0)
			(*act)->txt[1] = 'x';
		(*act)->pos = 2;
	}
	(*act)->s_txt += size;
	if (mod == 1)
		put_hex_sp((unsigned long long)hex, act, ASCII_B);
	if (mod == 0)
		put_hex_sp((unsigned long long)hex, act, ASCII_S);
	(*act)->act = 'x';
}
