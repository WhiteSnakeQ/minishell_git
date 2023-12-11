/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/11 14:21:37 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "project_f.h"
# include "get_next_line.h"

# define MALCERR "minishell: Malloc fail to create object\n"
# define ERRARG "minishell: Invalid number of arguments\n"
# define FILNF "minishell: command not found: "
# define SIGINT 2
# define SIGQUIT 3

# define NAME "\033[0;36m\033[1mminishell: \033[0m"

# define SET 0
# define GET 1

typedef struct s_argv
{
	char			*text;
	char			*name;
	struct s_argv	*next;
}					t_argv;

typedef struct s_prj
{
	char			*our_path;
	char			*name;
	char			*argv;
	char			**paths;
	char			**env;
	int				exit;
	int				skip;
	pid_t			pid;
	struct s_argv	*list_argv;
}					t_prj;

//					Modules
int			ft_printf(int descript, const char *str, ...);
int			print_error(char *message);
char		*get_next_line(int fd);
void		set_signals(void);
void		parse_argv(t_prj *prj);
void		make_action(t_prj *prj);

//					String_work
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strdup(char *src, int size);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strchr(const char *src, int symbol);
void		free_string(char *str);
void		free_strings(char **strs);
int			ft_strncmp(const char *s1, const char *s2, unsigned int n);
int			ft_strlen(const char *str);
void		*ft_memset(void *b, int c, size_t len);

//					Init_del_obj
t_argv		*init_argv(char *str);
void		clean_dirty(t_prj *prj);
void		init_prj(t_prj *prj, char **env);
void		clean_prj(int mod, t_prj **prj);
void		free_argv(t_argv *text);

#endif