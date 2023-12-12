/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:20:58 by kreys             #+#    #+#             */
/*   Updated: 2023/11/30 09:47:34 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project_f.h"

int	pud_build(int digit, int zero, t_action *act, int *iteraion)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (act->symb == '-' && zero == 1)
	{
		*iteraion += 1;
		ret += write(act->descriptor, "-", 1);
	}
	while (digit > i)
	{
		if (zero == 1)
			*iteraion += write(act->descriptor, "0", 1);
		else
			*iteraion += write(act->descriptor, " ", 1);
		i++;
	}
	return (ret);
}

char	*add_smb_s(char *str, int size_str, int size_padd, char symb)
{
	char	*str_ret;
	int		i;
	int		d;
	int		minus;

	d = 0;
	i = 0;
	minus = 0;
	if (str[d] == '-' && minus++ == 0)
		d++;
	str_ret = malloc(sizeof(char) * (size_padd + minus + 1));
	if (str[0] == '-')
		str_ret[i++] = '-';
	while (size_padd - (size_str - minus) > i - minus)
		str_ret[i++] = symb;
	while (size_padd + minus > i)
		str_ret[i++] = str[d++];
	str_ret[i] = '\0';
	free(str);
	return (str_ret);
}

void	chenge_str(t_action *act)
{
	int		minus;

	minus = 0;
	if (act->s_pnt == 0 && !act->txt[1] && act->txt[0] == '0')
	{
		act->s_txt = 0;
		return ;
	}
	if (act->txt[0] == '-')
		minus++;
	if (act->s_txt < act->s_pnt + minus)
		act->txt = add_smb_s(act->txt, act->s_txt, act->s_pnt, '0');
	act->s_txt = str_len(act->txt);
}

int	builder(t_action act)
{
	int		i;

	i = 0;
	if (act.point == 1 && act.act != 'd' && act.act != 'u' && act.act != 'x')
	{
		if (act.s_txt > act.s_pnt)
			act.s_txt = act.s_pnt;
	}
	else if (act.act != 'p' && act.act != 's' && act.point == 1)
		chenge_str(&act);
	if (act.point == 1)
		act.zero = 0;
	if (act.space == 1 && act.txt[0] != '-' && act.act != 's')
		act.count += write(act.descriptor, " ", 1);
	if (act.plus == 1 && act.txt[0] != '-')
		act.count += write(act.descriptor, "+", 1);
	act.symb = *act.txt;
	if (act.padding_left == 0)
		i += pud_build(act.s_pad - act.s_txt, act.zero, &act, &act.count);
	while (act.s_txt > i)
		act.count += write(act.descriptor, &act.txt[i++], 1);
	if (act.padding_left == 1)
		i += pud_build(act.s_pad - act.s_txt, 0, &act, &act.count);
	free(act.txt);
	return (act.count);
}
