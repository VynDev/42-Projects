NAME_NM = ft_nm
NAME_OTOOL = ft_otool

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I includes -I libft/includes

SOURCES_NM = main.c handle_elf.c handle_ar.c handle_64bits.c ft_putstr_c.c ft_strcmp_c.c
SOURCES_OTOOL = main.c

SRC_NM = $(addprefix src/nm/, $(SOURCES_NM))
OBJ_NM = $(SRC_NM:src/nm/%.c=obj/nm/%.o)

SRC_OTOOL = $(addprefix src/otool/, $(SOURCES_OTOOL))
OBJ_OTOOL = $(SRC_OTOOL:src/otool/%.c=obj/otool/%.o)


all: mylibft $(NAME_NM) $(NAME_OTOOL)

mylibft:
	make -C libft/

$(NAME_NM): nm_dir $(OBJ_NM)
	gcc $(FLAGS) $(OBJ_NM) -o $(NAME_NM) -L libft -lft

$(NAME_OTOOL): otool_dir $(OBJ_OTOOL)
	gcc $(FLAGS) $(OBJ_OTOOL) -o $(NAME_OTOOL) -L libft -lft

nm_dir:
	if [ ! -d "obj" ]; then mkdir obj; fi
	if [ ! -d "obj/nm" ]; then mkdir obj/nm; fi

otool_dir:
	if [ ! -d "obj" ]; then mkdir obj; fi
	if [ ! -d "obj/otool" ]; then mkdir obj/otool; fi

obj/%.o: src/%.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_NM)
	rm -f $(OBJ_OTOOL)

fclean: clean
	rm -f $(NAME_NM)
	rm -f $(NAME_OTOOL)
	make -C libft/ fclean

re: fclean all