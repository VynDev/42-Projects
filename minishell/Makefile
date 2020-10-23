NAME = minishell

FLAGS = -Wall -Werror -Wextra

SRCS =	main.c get_varpath.c file_check.c get_right_path.c tab_builtin.c data.c \
		builtin_exit.c builtin_cd.c builtin_env.c builtin_setenv.c builtin_unsetenv.c \
		builtin_echo.c split_wsquote.c ft_strsplit_quote.c debug_print.c get_input.c \
		term_config.c command.c builtin.c

INCLUDES = -I includes -I libft/includes

LIB = -L libft

OBJS = $(SRCS:.c=.o)

DEP = includes/minishell.h

all: mylibft $(NAME)

$(NAME): $(OBJS)

	gcc $(LIB) $(FLAGS) $(OBJS) -o $(NAME) -lft -ltermcap

mylibft:
	make -C libft/

%.o: srcs/%.c $(DEP)
	gcc $(FLAGS) $(INCLUDES) -c $<

clean:
	rm -f $(OBJS)
	make -C libft/ fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.NOTPARELLEL: all clean fclean re
