/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 02:38:51 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "project_f.h"
# include "get_next_line.h"

# define MALCERR "minishell: Malloc fail to create object\n"
# define ERRARG "minishell: Invalid number of arguments\n"

# define NAME "minishell: "

# define SETPRJ 0
# define CLPRJ 1

typedef struct s_prj
{
	char		*path;
	char		*name;
}				t_prj;

//					Modules
int			ft_printf(int descript, const char *str, ...);
int			print_error(char *message);
char		*get_next_line(int fd);

//					String_work
char		*ft_strdup(char *src);
void		free_string(char *str);

//					Init_del_obj
void		init_prj(t_prj *prj);
void		clean(int mod, t_prj **prj);

#endif