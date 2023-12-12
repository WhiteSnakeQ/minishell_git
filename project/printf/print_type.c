/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:49:35 by kreys             #+#    #+#             */
/*   Updated: 2023/11/04 20:19:37 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project_f.h"

void	chk_for_act(const char *str, va_list args, t_action **act)
{
	initialize(act);
	while (!(*act)->txt)
	{
		if (str[(*act)->skip] == 'c')
			put_char(va_arg(args, unsigned int), act);
		else if (str[(*act)->skip] == 's')
			put_str(va_arg(args, char *), act);
		else if (str[(*act)->skip] == 'p')
			prt_hex_adrs(va_arg(args, void *), act);
		else if (str[(*act)->skip] == 'd' || str[(*act)->skip] == 'i')
			put_decimal(va_arg(args, int), act);
		else if (str[(*act)->skip] == 'u')
			put_u_decimal(va_arg(args, unsigned int), act);
		else if (str[(*act)->skip] == 'x')
			put_hex_digit(va_arg(args, unsigned int), act, 0);
		else if (str[(*act)->skip] == 'X')
			put_hex_digit(va_arg(args, unsigned int), act, 1);
		else if (str[(*act)->skip] == '%')
			put_char('%', act);
		check_for_flags(str[(*act)->skip], act);
		(*act)->skip++;
	}
}

void	check_for_flags(char c, t_action **act)
{
	if (c == '-')
		(*act)->padding_left = 1;
	else if (c == '0' && ((*act)->s_pad == 0 && (*act)->point == 0))
		(*act)->zero = 1;
	else if (c == '.')
		(*act)->point = 1;
	else if (c == '#')
		(*act)->sharp = 1;
	else if (c == '*')
		(*act)->width = 1;
	else if (c == ' ')
		(*act)->space = 1;
	else if (c == '+')
		(*act)->plus = 1;
	else if (c >= '0' && c <= '9' && (*act)->point == 0)
		(*act)->s_pad = ((*act)->s_pad * 10) + (c - '0');
	else if (c >= '0' && c <= '9')
		(*act)->s_pnt = ((*act)->s_pnt * 10) + (c - '0');
}
