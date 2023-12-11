# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 00:25:58 by kreys             #+#    #+#              #
#    Updated: 2023/12/11 14:19:29 by kreys            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRC				= minishell.c \
				  del_obj.c \
				  init_obj.c \
				  string.c \
				  string2.c \
				  string3.c \
				  error_handle.c \
				  free_module.c \
				  signals.c \
				  text_create.c \
				  make_act.c \

SRCDIR			= ./project/minishell/
SRCOBJ			= ${addprefix ${SRCDIR}, ${SRC:.c=.o}}

GNLSRC			= get_next_line.c get_next_line_utils.c
GNLSIR			= ./project/get_next_line/
GNLOBJ			= ${addprefix ${GNLSIR}, ${GNLSRC:.c=.o}}

PRFSRC			= libftprintf.a
PRFDIR			= ./project/ft_printf/
PRFOBJ			= ${addprefix ${PRFDIR}, ${PRFSRC}}

CC				= cc
FLAGS			= -g -gdwarf-4 -Wall -Wextra -Werror -fsanitize=address

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
