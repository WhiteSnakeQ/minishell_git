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
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "project_f.h"
# include "get_next_line.h"

# define MALCERR "minishell: Malloc fail to create object\n"
# define ERRARG "minishell: Invalid number of arguments\n"
# define FILNF "minishell: command not found: "
# define INVEXIT "minishell: exit: too many arguments "
# define INVNARG "minishell: cd: too many arguments"
# define NOFILEORDIR "No such file or directory"
# define CORE_D "Quit (core dumped)\n"
# define NUMREC "numeric argument required"

# define SIGINT 2
# define SIGQUIT 3

# define NAME "\033[0;36m\033[1mminishell: \033[0m"

# define SET 0
# define GET 1

# define NL 0
# define NNL 1

# define NCLEAN 0
# define CLEAN 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;


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
	char			**env_str;
	int				skip;
	pid_t			pid;
	struct s_argv	*list_argv;
	struct s_env	*env;
}					t_prj;

//					Modules
int			ft_printf(int descript, const char *str, ...);
int			print_error(char *message);
int			check_error(t_prj *prj);
char		*get_next_line(int fd);
void		set_signals(t_prj *prj);
void		parse_argv(t_prj *prj);
void		make_action(t_prj *prj);

//					String_work
char		**ft_split(char const *s, char c);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strdup(char *src, int size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strchr(const char *src, int symbol);
char		*new_str_after(char *env, char symbl);
char		*new_str_till(char *env, char symbl);
char    	*create_one_env(t_env *env);
char		*del_symbl(char *str, char *symbl);
char		*create_str(int size);
char		*cover_char(char *str, char symb);
void		*ft_memset(void *b, int c, size_t len);
void		print_strings(char **strs, int modprnt, int mod);
void		free_string(char *str);
void		free_strings(char **strs);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, unsigned int n);
int			ft_strlen(const char *str);
int			calc_size_strs(char **strs);
int			ft_isdigit(char *str);
int			ft_atoi(const char *str);

//					Function
void    	pwd(char **strs, t_prj *prj);
void    	cd(char **strs, t_prj *prj);
void    	echo(char **strs, t_prj *prj);
void   		exit_m(char **strs, t_prj *prj);

//					Work_with_env
char		**make_env_str(t_env *env);
void		env_add_last(t_prj *prj, char *str);
void		env_remove_key(t_prj *prj, char *key);

//					Init_del_obj
t_argv		*init_argv(char *str);
void		clean_dirty(t_prj *prj);
void		init_prj(t_prj *prj, char **env);
void		clean_prj(int mod, t_prj **prj);
void		free_argv(t_argv *text);
void		free_env(t_env *env);

#endif