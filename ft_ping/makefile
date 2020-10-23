NAME = ft_ping

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I includes -I libft/includes

SOURCES = main.c env.c init_socket.c checksum.c ping_send.c ping_recv.c set_hdr.c print_stats.c
 
SRC = $(addprefix src/, $(SOURCES))
OBJ = $(SRC:src/%.c=obj/%.o)



all: mylibft $(NAME)

mylibft:
	make -C libft/

$(NAME): dir $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME) -L libft -lft


dir:
	if [ ! -d "obj" ]; then mkdir obj; fi

obj/%.o: src/%.c includes/ft_ping.h
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all