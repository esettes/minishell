# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/08 19:37:36 by ulherrer          #+#    #+#              #
#    Updated: 2024/01/25 21:27:15 by iostancu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN	= \033[0;32m
RESET	= \033[0m
GREY	= \033[1;30m
LWHITE	= \033[2;37m
LGREEN	= \033[2;32m

NAME = libft.a
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror -pedantic
INCLUDE = -I include -I ./inc/

SOURCES = \
ft_atoi.c \
ft_atol.c \
ft_itoa.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isxdigit.c \
ft_isprint.c \
ft_isspace.c \
ft_isupper.c \
ft_islower.c \
ft_toupper.c \
ft_tolower.c \
ft_bzero.c \
ft_memccpy.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_calloc.c \
ft_split.c \
ft_split_split.c \
ft_strchr.c \
ft_strdup.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_striteri.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_puterror.c \
ft_strrev.c \
ft_time_diff.c \
ft_time_now.c \
ft_lstadd_back_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstclear_bonus.c \
ft_lstdelone_bonus.c \
ft_lstiter_bonus.c \
ft_lstlast_bonus.c \
ft_lstmap_bonus.c \
ft_lstnew_bonus.c \
ft_lstsize_bonus.c

SRCDIR = src/
SRC	= $(addprefix $(SRCDIR), $(SOURCES))
OBJDIR	= src/obj/
OBJS	= $(addprefix $(OBJDIR), $(SOURCES:.c=.o))

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "${LWHITE}$(NAME) ${LGREEN}✓$(RESET)"

all: obj $(NAME)

obj:
	@mkdir -p $(OBJDIR)

clean:
	@/bin/rm -rf $(OBJS)
	@echo "${LWHITE}Clean libft... ${LGREEN}✓$(RESET)"

fclean: 
	@/bin/rm -rf $(OBJS)
	@/bin/rm -rf $(NAME)

f: fclean
re: fclean all

.PHONY: all clean fclean f re
