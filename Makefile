# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 00:25:58 by kreys             #+#    #+#              #
#    Updated: 2023/12/16 18:01:42 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRC				= ./main_project/minishell.c \
				  ./main_project/del_obj.c \
				  ./main_project/init_obj.c \
				  ./main_project/error_handle.c \
				  ./main_project/free_module.c \
				  ./main_project/signals.c \
				  ./main_project/wildcast.c \
				  ./env_work/env.c \
				  ./env_work/env_additional.c \
				  ./function/pwd.c \
				  ./function/cd.c \
				  ./function/echo.c \
				  ./function/exit.c \
				  ./function/export.c \
				  ./function/unset.c \
				  ./function/env.c \
				  ./parse_cmd/text_create.c \
				  ./parse_cmd/parse_quote.c \
				  ./parse_cmd/merge_text.c \
				  ./parse_cmd/check_cmd.c \
				  ./parse_cmd/redirect.c \
				  ./parse_cmd/additional_cmd.c \
				  ./parse_cmd/create_cmd.c \
				  ./parse_cmd/additional.c \
				  ./exec/start.c \
				  ./exec/fd.c \
				  ./exec/check.c \
				  ./exec/my_exec.c \
				  ./string_opr/string.c \
				  ./string_opr/string2.c \
				  ./string_opr/string3.c \
				  ./string_opr/string4.c \
				  ./string_opr/string5.c \
				  ./string_opr/string6.c \
				  ./string_opr/string7.c \

SRCDIR			= ./project/minishell/
SRCOBJ			= ${addprefix ${SRCDIR}, ${SRC:.c=.o}}

GNLSRC			= get_next_line.c get_next_line_utils.c
GNLSIR			= ./project/get_next_line/
GNLOBJ			= ${addprefix ${GNLSIR}, ${GNLSRC:.c=.o}}

PRFSRC			= libftprintf.a
PRFDIR			= ./project/printf/
PRFOBJ			= ${addprefix ${PRFDIR}, ${PRFSRC}}

CC				= cc
FLAGS			= -g -Wall -Wextra -Werror

ALLOBJ			=  ${SRCOBJ} ${GNLOBJ} ${PRFOBJ}

all:			 create_prj ${NAME} clean

.c.o:
				@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${ALLOBJ}
				@${CC} ${FLAGS} ${ALLOBJ} -lreadline -lhistory -o ${NAME} 
				@echo DONE

create_prj:		
				@${MAKE} -C ${PRFDIR}

clean:			
				@rm -f ${ALLOBJ}

fclean:			clean
				@rm -f ${NAME}

re:				fclean all clean

#valgrind --suppressions=readline.supp --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --gen-suppressions=no --quiet ./minishell 