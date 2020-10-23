NAME_CLIENT = client
NAME_SERVER = server

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I includes -I libft/includes

SOURCES_COMMON = ../common/cbuffer.c ../common/c_exit.c ../common/build_packet.c ../common/get_packet.c ../common/get_command.c ../common/send_packet.c
SOURCES_CLIENT = $(SOURCES_COMMON) main.c init_env.c init_fdset.c main_loop.c read_fds.c get_message.c parse_input.c recvcmd_msg.c memslots.c
SOURCES_SERVER = $(SOURCES_COMMON) main.c init_env.c init_server.c main_loop.c init_fdset.c read_fds.c get_message.c user_joinchannel.c user_leavechannel.c recvcmd_msg.c recvcmd_nick.c recvcmd_join.c recvcmd_who.c recvcmd_leave.c \
					sendmsg_to_channel.c sendmsg_to_user.c memslots.c
 
SRC_CLIENT = $(addprefix src/client/, $(SOURCES_CLIENT))
OBJ_CLIENT = $(SRC_CLIENT:src/client/%.c=obj/client/%.o)

SRC_SERVER = $(addprefix src/server/, $(SOURCES_SERVER))
OBJ_SERVER = $(SRC_SERVER:src/server/%.c=obj/server/%.o)


all: mylibft $(NAME_CLIENT) $(NAME_SERVER)

mylibft:
	make -C libft/

$(NAME_CLIENT): client_dir $(OBJ_CLIENT)
	gcc $(FLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT) -L libft -lft

$(NAME_SERVER): server_dir $(OBJ_SERVER)
	gcc $(FLAGS) $(OBJ_SERVER) -o $(NAME_SERVER) -L libft -lft

client_dir:
	if [ ! -d "obj" ]; then mkdir obj; fi
	if [ ! -d "obj/client" ]; then mkdir obj/client; fi
	if [ ! -d "obj/common" ]; then mkdir obj/common; fi

server_dir:
	if [ ! -d "obj" ]; then mkdir obj; fi
	if [ ! -d "obj/server" ]; then mkdir obj/server; fi
	if [ ! -d "obj/common" ]; then mkdir obj/common; fi

obj/%.o: src/%.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT)
	rm -f $(OBJ_SERVER)

fclean: clean
	rm -f $(NAME_CLIENT)
	rm -f $(NAME_SERVER)
	make -C libft/ fclean

re: fclean all