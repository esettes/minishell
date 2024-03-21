# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 18:59:41 by iostancu          #+#    #+#              #
#    Updated: 2024/03/13 23:19:17 by iostancu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN	= \033[0;32m
RESET	= \033[0m
GREY	= \033[1;30m
LWHITE	= \033[2;37m
LGREEN	= \033[2;32m

NAME	= ft_printf.a
SRCS	= ft_printf.c string_chars.c put_nbr.c nbr_base.c
OBJS	= ${SRCS:.c=.o}
CC		= gcc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -g
AR		= ar rc
INC		= -I include -I ./inc

.c.o:
	@${CC} ${CFLAGS} ${INC} -o $@ -c $<
#${<:.c=.o}

${NAME}:	${OBJS}
		@${AR} ${NAME} ${OBJS}
		@ranlib ${NAME}
		@echo "${LWHITE}$(NAME) ${LGREEN}✓$(RESET)"
clean:
		@${RM} ${OBJS}
		@echo "${LWHITE}Clean ft_printf... ${LGREEN}✓$(RESET)"

all:	${NAME}

fclean:
		@${RM} ${OBJS}
		@${RM} ${NAME}

re:		fclean all

.PHONY: re
