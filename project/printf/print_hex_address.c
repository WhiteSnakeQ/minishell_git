/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:16:15 by kreys             #+#    #+#             */
/*   Updated: 2023/11/04 20:19:39 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project_f.h"

void	prt_hex_adrs(void *ptr, t_action **act)
{
	int		size;

	size = calculate_size((unsigned long long)ptr) + 2;
	if (check_for_hex((unsigned long long)ptr) == 1)
		size += 1;
	(*act)->txt = malloc (sizeof(char) * (size + 1));
	(*act)->txt[size] = '\0';
	(*act)->txt[0] = '0';
	(*act)->txt[1] = 'x';
	(*act)->pos = 2;
	(*act)->s_txt += size;
	put_hex_sp((unsigned long long)ptr, act, (char *)ASCII_S);
}
