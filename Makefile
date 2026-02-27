CC			= c++
NAME		= life
CFLAGS		= -std=c++20 -Wall -Wextra -Werror -I$(DIR_INC)
SRCFILES	= main.cpp Life.cpp
HEADERFILES	= Life.hpp
DEFAULT_MAP	= test_map
MAP			:= $(or $(MAP), $(DEFAULT_MAP)) 

DIR_MAP		= maps/
DIR_SRC		= src/
DIR_OBJ		= obj/
DIR_INC		= include/

HPP_LOC		= $(addprefix $(DIR_INC), $(HEADERFILES))
ALL_OBJ		= $(addprefix $(DIR_OBJ), $(SRCFILES:.cpp=.o))
MAP_LOC		= $(addprefix $(DIR_MAP), $(MAP))

VPATH		= $(DIR_SRC)

#----------------------------------------------------------------------------

all: $(NAME)
re: fclean all
clean:; rm -rf $(DIR_OBJ)
fclean: clean; rm -f $(NAME)
.PHONY: clean fclean re all

$(NAME): $(ALL_OBJ)
	$(CC) $(CFLAGS) $(ALL_OBJ) -o $(NAME)

$(DIR_OBJ)%.o: %.cpp $(HPP_LOC) | $(DIR_OBJ)
	$(CC) -c $(CFLAGS) -o $@ $<

$(DIR_OBJ):
	mkdir $@ 

fsan: $(ALL_OBJ)
	@echo "compiling with fsanitize flag"
	$(CC) $(CFLAGS) $(ALL_OBJ) -fsanitize=address -o $(NAME)

#makefile usage: using "make run" will run the default map, test_map.
#you can add "MAPS="name_of_map"" select a different map
run: $(NAME) 
	./$(NAME) $(MAP_LOC)

valg: $(NAME)
	valgrind ./$(NAME)

ccommands:
	$(MAKE) fclean
	$(CC) $(CFLAGS) -c -o $@ $<
