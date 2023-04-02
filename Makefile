NAME = webserv

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -fsanitize=undefined

INC_DIR = ./inc/
SRC_DIR = ./src/
OBJ_DIR = ./obj/

INC_FILES = Client.hpp Inc.hpp Location.hpp Parser.hpp Pollge.hpp\
						Request.hpp Response.hpp Serverconf.hpp
SRC_FILES = main.cpp Client.cpp Location.cpp Parser.cpp Pollge.cpp\
						Request.cpp Response.cpp Serverconf.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)

INC = $(addprefix $(INC_DIR), $(INC_FILES))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

MKDIR = @mkdir -p $(OBJ_DIR)

all : $(NAME)

$(NAME) : $(INC) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(MKDIR)
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(INC_DIR)

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -rf $(NAME)

re : fclean all