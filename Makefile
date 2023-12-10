# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kreys <kirrill20030@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 00:25:58 by kreys             #+#    #+#              #
#    Updated: 2023/12/11 02:42:41 by kreys            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRC				= minishell.c \
				  del_obj.c \
				  init_obj.c \
				  string.c \
				  error_handle.c \
				  free_module.c

SRCDIR			= ./project/minishell/
SRCOBJ			= ${addprefix ${SRCDIR}, ${SRC:.c=.o}}

GNLSRC			= get_next_line.c get_next_line_utils.c
GNLSIR			= ./project/get_next_line/
GNLOBJ			= ${addprefix ${GNLSIR}, ${GNLSRC:.c=.o}}

PRFSRC			= libftprintf.a
PRFDIR			= ./project/ft_printf/
PRFOBJ			= ${addprefix ${PRFDIR}, ${PRFSRC}}

CC				= cc
FLAGS			= -Wall -Wextra -Werror -gdwarf-4

ALLOBJ			=  ${SRCOBJ} ${GNLOBJ} ${PRFOBJ}

all:			 create_prj ${NAME} clean

.c.o:
				${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${ALLOBJ}
				${CC} ${FLAGS} ${ALLOBJ} -o ${NAME}
				@echo DONE

create_prj:		
				@${MAKE} -C ${PRFDIR}

clean:			
				@rm -f ${ALLOBJ}

fclean:			clean
				@rm -f ${NAME}

re:				fclean all clean
