NAME = multilayer_perceptron

COMPILER = g++

FLAGS =

INCLUDES = -I includes -I lib/libnn/includes

LIBS = -L lib/libnn
LINKER = -lnn

SOURCES = main.cpp debug.cpp csv.cpp extract.cpp scaledata.cpp neuralnetmanager.cpp Train.cpp Validate.cpp
 
SRC = $(addprefix sources/, $(SOURCES))
OBJ = $(SRC:sources/%.cpp=obj/%.o)

all: dir mylibnn $(NAME)

mylibnn:
	make -C lib/libnn/

$(NAME): $(OBJ) lib/libnn/libnn.a
	$(COMPILER) $(FLAGS) $(OBJ) -o $(NAME) $(LIBS) $(LINKER)

dir:
	if [ ! -d "obj" ]; then mkdir obj; fi

obj/%.o: sources/%.cpp lib/libnn/libnn.a
	$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make -C lib/libnn/ fclean

re: fclean all