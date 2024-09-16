NAME = libft.a
CC = gcc

GREEN	= \033[0;32m
RESET	= \033[0m
GREY	= \033[1;30m
LWHITE	= \033[2;37m
LGREEN	= \033[2;32m


SRCS = ft_atoi.c \
	ft_isprint.c \
	ft_putchar_fd.c \
	ft_striteri.c \
	ft_strnstr.c \
	ft_bzero.c \
	ft_itoa.c \
	ft_putendl_fd.c \
	ft_strjoin.c \
	ft_strrchr.c \
	ft_calloc.c \
	ft_memchr.c \
	ft_putnbr_fd.c \
	ft_strlcat.c \
	ft_strtrim.c \
	ft_isalnum.c \
	ft_memcmp.c \
	ft_putstr_fd.c \
	ft_strlcpy.c \
	ft_substr.c \
	ft_isalpha.c \
	ft_memcpy.c \
	ft_split.c \
	ft_strlen.c \
	ft_tolower.c \
	ft_isascii.c \
	ft_memmove.c \
	ft_strchr.c \
	ft_strmapi.c \
	ft_toupper.c \
	ft_isdigit.c \
	ft_memset.c \
	ft_strdup.c \
	ft_strncmp.c \
	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c \
	ft_printf.c \
	ft_printf_chr.c \
	ft_printf_hex.c \
	ft_printf_num.c \
	ft_printf_ptr.c \
	ft_printf_str.c \
	ft_print_error.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_free_matrix.c \
	ft_count_chars_str.c \
	ft_puterror.c \
	ft_strcmp.c \
	ft_isblank.c

SRC_DIR = src/

SRC	= $(addprefix $(SRC_DIR), $(SRCS))
OBJ_DIR	= src/obj/
OBJS	= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

CFLAGS = -Werror -Wextra -Wall

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I . -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS) 
	@ar rc $(NAME) $(OBJS)
	@echo "${LWHITE}$(NAME) ${LGREEN}✓$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "${LWHITE}Clean libft... ${LGREEN}✓$(RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all
