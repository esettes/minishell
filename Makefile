# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/21 19:03:34 by uliherre          #+#    #+#              #
#    Updated: 2024/08/27 19:13:05 by antosanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN	= \033[0;32m
RESET	= \033[0m
GREY	= \033[1;30m
LWHITE	= \033[2;37m
LGREEN	= \033[2;32m

NAME = minishell

CC = clang
CFLAGS = -g3 -fsanitize=address #-Wall -Wextra -Werror #-fsanitize-ignorelist=/home/settes/cursus/minishell/ignorelist.txt #-Wall -Wextra -Werror -pedantic
LDFLAGS	= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
CFLAGS += -I/Users/$(USER)/.brew/opt/readline/include

INCLUDES = -I include -I ./inc/headers -I ./inc/libft/inc

############################ PARSER ###########################
DIR_PARSER = ./src/myownparse/
SOURCES_PARSER = \
	expander_utils.c \
	expander.c \
	heredoc.c \
	lex_utils.c \
	lex.c \
	list_utils.c \
	parser.c \
	validator.c \
	yacc_utils.c \
	yacc.c

A_PARSER = $(addprefix $(DIR_PARSER),$(SOURCES_PARSER))
SOURCES = $(A_PARSER)
OBJECTS = $(addprefix $(OBJDIR), $(SOURCES_PARSER:.c=.o))

############################ SHELL ############################
DIR_SHELL = ./src/sources_shell/
SOURCES_SHELL = \
	core_shell.c \
	main.c \
	signal.c \
	prompt.c

A_SHELL = $(addprefix $(DIR_SHELL),$(SOURCES_SHELL))
SOURCES += $(A_SHELL)
OBJECTS += $(addprefix $(OBJDIR), $(SOURCES_SHELL:.c=.o))

########################## BUILTIN ############################
DIR_BUILTIN = ./src/builtin/
SOURCES_BUILTIN = \
	echo.c \
	export.c \
	unset.c \
	cd.c \
	env.c \
	exit.c \
	pwd.c \
	env_utils.c \
	env_utils_2.c \
	env_utils_3.c

A_BUILTIN = $(addprefix $(DIR_BUILTIN),$(SOURCES_BUILTIN))
SOURCES += $(A_BUILTIN)
OBJECTS += $(addprefix $(OBJDIR), $(SOURCES_BUILTIN:.c=.o))

########################## PIPEX ##############################
DIR_PIPEX = ./src/pipex/
SOURCES_PIPEX = \
	f_split.c \
	lib_utils.c \
	lib_utils_2.c \
	pipex.c \
	processes.c \
	utils.c \
	utils_2.c \
	utils_3.c

A_PIPEX = $(addprefix $(DIR_PIPEX),$(SOURCES_PIPEX))
SOURCES += $(A_PIPEX)
OBJECTS += $(addprefix $(OBJDIR), $(SOURCES_PIPEX:.c=.o))

###############################################################

OBJDIR = ./src/obj/

LIBFT = ./inc/libft/libft.a

COMPS = $(LIBFT)

$(OBJDIR)%.o:$(DIR_PARSER)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR)%.o:$(DIR_SHELL)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR)%.o:$(DIR_EXECUTER)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR)%.o:$(DIR_BUILTIN)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR)%.o:$(DIR_PIPEX)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJECTS) $(COMPS)
	@$(CC) $(CFLAGS)  $(INCLUDES) $(OBJECTS) $(LDFLAGS) $(COMPS) -o $(NAME)
	@echo "${LWHITE}$(NAME) ${LGREEN}✓$(RESET)"
	@echo "${GREY}Compilation ${GREEN}[OK]$(RESET)"

$(LIBFT):
	@$(MAKE) -sC $(dir $(LIBFT))


all: obj $(NAME)

obj:
	@mkdir -p $(OBJDIR)

clean:
	@/bin/rm -rf $(OBJECTS)
	@$(MAKE) -sC $(dir $(LIBFT)) clean
	@echo "${LWHITE}Clean minishell... ${LGREEN}✓$(RESET)"

fclean: clean
	@/bin/rm -rf $(NAME)
	@$(MAKE) -sC $(dir $(LIBFT)) fclean

f: fclean

re: fclean all

.PHONY: all clean fclean f re
