ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

FLAGS = -Wall -Werror -Wextra -fPIC

INCLUDES = -I includes -I libft/includes

SOURCES = malloc.c realloc.c free.c allocate.c utils.c ft_putbase.c show_alloc_mem.c create_large.c alloc_zone.c init_zone.c free_zone.c free_large.c

TEST_SOURCES = main.c tests_tiny.c tests_small.c tests_large.c tests_printf.c tests_realloc.c

SRC = $(addprefix src/, $(SOURCES))
OBJ = $(SRC:src/%.c=obj/%.o)

TEST_SRC = $(addprefix tests/, $(TEST_SOURCES))

all: objdir mylibft $(NAME)

objdir:
	 if [ ! -d "obj" ]; then mkdir obj; fi

mylibft:
	make -C libft/ FLAGS="$(FLAGS)"

$(NAME): $(OBJ)
	gcc -shared $(FLAGS) $(OBJ) -o $(NAME) -L libft -lft

obj/%.o: src/%.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

test: all
	gcc $(FLAGS) $(INCLUDES) tests/tests_empty.c -o test_malloc_empty -L . -lft_malloc_$(HOSTTYPE) -L libft -lft && ./test_malloc_empty
	gcc $(FLAGS) $(INCLUDES) tests/tests_tiny.c -o test_malloc_tiny -L . -lft_malloc_$(HOSTTYPE) -L libft -lft && ./test_malloc_tiny
	gcc $(FLAGS) $(INCLUDES) tests/tests_small.c -o test_malloc -L . -lft_malloc_$(HOSTTYPE) -L libft -lft && ./test_malloc
	gcc $(FLAGS) $(INCLUDES) tests/tests_large.c -o test_malloc -L . -lft_malloc_$(HOSTTYPE) -L libft -lft && ./test_malloc
	gcc $(FLAGS) $(INCLUDES) tests/tests_printf.c -o test_malloc -L . -lft_malloc_$(HOSTTYPE) -L libft -lft && ./test_malloc
	gcc $(FLAGS) $(INCLUDES) tests/tests_realloc.c -o test_malloc -L . -lft_malloc_$(HOSTTYPE) -L libft -lft && ./test_malloc
	gcc $(FLAGS) $(INCLUDES) tests/tests_free2.c -o test_malloc -L . -lft_malloc_$(HOSTTYPE) -L libft -lft && ./test_malloc
	gcc $(FLAGS) $(INCLUDES) tests/tests_realloc2.c -o test_malloc -L . -lft_malloc_$(HOSTTYPE) -L libft -lft && ./test_malloc
	gcc $(FLAGS) $(INCLUDES) tests/tests_realloc3.c -o test_malloc -L . -lft_malloc_$(HOSTTYPE) -L libft -lft && ./test_malloc
	gcc $(FLAGS) $(INCLUDES) tests/tests_error.c -o test_malloc -L . -lft_malloc_$(HOSTTYPE) -L libft -lft && ./test_malloc
