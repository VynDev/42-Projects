NAME = ft_ls

FLAGS = -Wall -Werror -Wextra

SRCS =	main.c list_dir.c args.c print.c get.c sort.c getmax.c check.c del.c \
		get_info.c get_dir.c print_color.c

INCLUDES = -I includes -I libft/includes

LIB = -L libft

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): mylibft $(OBJS)

	gcc $(LIB) $(FLAGS) $(OBJS) -o $(NAME) -lft

mylibft:
	make -C libft/

%.o: srcs/%.c
	gcc $(FLAGS) $(INCLUDES) -c $<

clean:
	rm -f $(OBJS)
	make -C libft/ fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.NOTPARALLEL: all clean fclean re
