CC			= c++
NAME		= life
CFLAGS		= -std=c++20 -Wall -Wextra -Werror -I$(DIR_INC)
SRCFILES	= main.cpp Life.cpp
HEADERFILES	= Life.hpp

DIR_SRC		= src/
DIR_OBJ		= obj/
DIR_INC		= include/

HPP_LOC		= $(addprefix $(DIR_INC), $(HEADERFILES))
ALL_OBJ		= $(addprefix $(DIR_OBJ), $(SRCFILES:.cpp=.o))

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

run: $(NAME)
	./$(NAME) maps/test_map

valg: $(NAME)
	valgrind ./$(NAME)

ccommands:
	$(MAKE) fclean
	$(CC) $(CFLAGS) -c -o $@ $<
