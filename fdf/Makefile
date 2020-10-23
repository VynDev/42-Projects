NAME = fdf

FLAGS = -Wall -Werror -Wextra

SRCS = main.c draw.c utility.c input.c show_iso.c setup.c

INCLUDES = -I includes -I libft/includes

LIB = -L libft -L lib

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): mylibft $(OBJS)
	
	gcc $(LIB) $(FLAGS) $(OBJS) -o $(NAME) -lft -lmlx -framework OpenGL -framework AppKit

mylibft:
	make -C libft/

%.o: srcs/%.c
	gcc $(FLAGS) $(INCLUDES) -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

send: fclean
	git add *
	git commit -m "Send"
	git push

get:
	git pull

run: all
	./$(NAME)

rrun: get all
	./$(NAME)