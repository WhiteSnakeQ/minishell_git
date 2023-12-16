/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:07:51 by kreys             #+#    #+#             */
/*   Updated: 2023/12/16 17:40:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	print_error(char *message)
{
	printf("%s", message);
	clean_prj(GET, NULL);
	return (1);
}
