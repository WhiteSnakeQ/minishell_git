/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:49:51 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 00:37:15 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char		*strjoins(char *s1, char *s2, int size1, int size2);
char		*clean_str(char *str, int i);
char		*read_file(char *full_str, int file);
char		*read_str(char	*str);

int			strlens(char *str);
int			check_new_line(char *str);

#endif