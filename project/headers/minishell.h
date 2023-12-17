/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:16:04 by kreys             #+#    #+#             */
/*   Updated: 2023/12/17 09:32:42 by kreys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "get_next_line.h"
# include "project_f.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define MALCERR "minishell: Malloc fail to create object\n"
# define CDOLD "minishell: cd: OLDPWD not set\n"
# define CDHOME "minishell: cd: HOME not set\n"
# define ERRARG "minishell: Invalid number of arguments\n"
# define PIPERR "minishell: Pipe failed\n"
# define PEDERR "minishell: Fork failed\n"
# define FILNF "minishell: command not found: "
# define UNEXPTOKS "minishell: syntax error near unexpected token "
# define UNEXPTOKN "minishell: syntax error near unexpected token `newline'\n"
# define UNEXPTOK "minishell: syntax error near unexpected token `|'\n"
# define INVEXIT "minishell: exit: too many arguments "
# define INVNARG "minishell: cd: too many arguments\n"
# define NOFILEORDIR "No such file or directory"
# define CORE_D "Quit (core dumped)\n"
# define NUMREC "numeric argument required"
# define NVID " not a valid identifier"

# define SIGINT 2
# define SIGQUIT 3

# define NAME "\033[0;36m\033[1mminishell: \033[0m"

# define SET 0
# define GET 1

# define NL 0
# define NNL 1

# define NCLEAN 0
# define CLEAN 1

# define SINGLE 0
# define DOUBLE 1

typedef struct s_helper_env
{
	struct s_env	*prev;
	struct s_env	*next;
	struct s_env	**addres;
	struct s_env	*first;
}	t_hlp;

typedef struct s_helper
{
	int				i;
	int				j;
	int				c;
	char			ch;
	char			*str;
}					t_helper;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_text
{
	char			*text;
	struct s_text	*next;
}					t_text;

typedef struct s_argv
{
	char			*text;
	int				ex;
	struct s_argv	*next;
}					t_argv;

typedef struct s_cmd
{
	char			*cmd_name;
	char			**argv;
	pid_t			pid;
	int				valid;
	int				file_inp;
	int				redirect_inp;
	int				file_fd_out;
	int				redirect_out;
	int				olddesl;
	int				*pipe;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_prj
{
	char			*our_path;
	char			*name;
	char			*argv;
	char			**paths;
	char			**env_str;
	int				*pipeold;
	int				skip;
	int				parsing;
	int				exit;
	char			*l_cmd;
	pid_t			curr;
	pid_t			pid;
	struct s_argv	*list_argv;
	struct s_env	*env;
	struct s_cmd	*cmd;
}					t_prj;

//					Modules
int					ft_printf(int descript, const char *str, ...);
int					print_error(char *message);
char				*get_next_line(int fd);
void				signal_quit(int syg);
void				execute_cmd(t_prj *prj, t_cmd *cmd, int f_ex, int mod);
void				make_wildcast(t_prj *prj, t_argv *argv);

//					Some_Signals
void				set_signal_ignore(void);
void				set_signals(t_prj *prj, int mod);
void				signal_sig(int syg);
void				write_in_zero(int mod, char *new_str);

//					Parse_param
int					check_cmd(t_argv **argv);
int					check_sp_smb_arv(t_argv *argv);
char				*make_full(char *str, t_prj *prj, int m_size, int i);
void				check_for_ex(t_prj *prj);
void				add_last_cmd(t_cmd **cmd, t_cmd *new);
void				parse_argv(t_prj *prj);
void				parse_quotet(t_prj *prj);
void				make_cmd(t_prj *prj, t_argv *argv, int l_ex);

//					String_work
int					copy_to(t_helper *p, t_prj *prj, int *srt, char *ret);
int					check_dollr(char *str, int i, t_prj *prj);
int					ft_strlcpy(char *dest, const char *src, size_t size);
int					symbl_in_str(char *str, char symb);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
int					ft_strlen(const char *str);
int					calc_size_strs(char **strs);
int					ft_isdigit(char *str);
int					ft_atoi(const char *str);
int					check_all_cmd(char *str);
char				**ft_split(char const *s, char c);
char				*took_puth(t_prj *prj, t_cmd *cmd);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strdup(char *src, int size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strchr(const char *src, int symbol);
char				*new_str_after(char *env, char symbl);
char				*new_str_till(char *env, char symbl);
char				*create_one_env(t_env *env);
char				*del_symbl(char *str, char *symbl);
char				*create_str(int size);
char				*cover_char(char *str, char symb);
char				*ft_itoa(int n, char *clean);
char				*add_to_end(char *str, char symb);
char				*add_to_start(char *str, char symb);
void				*ft_memset(void *b, int c, size_t len);
void				print_strings(char **strs, int modprnt, int mod);
void				free_string(char *str);
void				free_strings(char **strs);
void				ft_sort_params(char **tab, int size);

//					Function
void				pwd(char **strs, t_prj *prj, int fd);
void				cd(char **strs, t_prj *prj, int fd);
void				echo(char **strs, t_prj *prj, int fd);
void				exit_m(char **strs, t_prj *prj);
void				export(char **strs, t_prj *prj, int fd);
void				env(char **strs, t_prj *prj, int fd);
void				unset(char **strs, t_prj *prj);
int					my_execve(t_prj *prj, t_cmd *cmd, int mod);

//					Work_with_env
char				**make_env_str(t_env *env);
char				**export_all(t_env *env, int size);
char				*get_value_env_str(char *key, t_env *env);
void				env_add_last(t_prj *prj, char *str);
void				env_remove_key(t_prj *prj, char *key);
int					env_change_key(t_prj *prj, char *key, char *new_val);
int					get_value_env_int(char *key, t_env *env);

//					Fd_operation
void				close_if_op(t_cmd *cmd, int mod);
void				close_fd(int fd);
void				write_in_fd(t_cmd *cmd, t_cmd *cmd2);
void				close_all(t_prj *prj);
void				change_fd_write(t_cmd *cmd, int mod, char *str);
void				change_fd_read(t_cmd *cmd, int mod, char *str, t_prj *prj);

//					Init_del_obj
t_argv				*init_argv(char *str);
t_cmd				*init_cmd(void);
void				clean_dirty(t_prj *prj);
void				init_prj(t_prj *prj, char **env);
void				clean_prj(int mod, t_prj **prj);
void				free_text(t_text *text);
void				free_argv(t_argv *text);
void				free_env(t_env *env);
void				free_cmd(t_cmd *cmd);
void				free_one_argv(t_argv *argv);

#endif