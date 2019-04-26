##
## EPITECH PROJECT, 2018
## makefile
## File description:
## makefile
##

NAME	=	bomberman

CC	=	g++

RM	=	rm -f

SRCS	=	src/create_map.cpp	\
		src/main.cpp		\
		src/items.cpp		\
		src/boom.cpp		\
		src/player.cpp		\
		src/game.cpp		\
		lib_test/sdl.cpp	\
		src/items_bonus.cpp	\

OBJS	=	$(SRCS:.cpp=.o)

CPPFLAGS =	-I ./include/
CPPFLAGS +=	-W -Wall -Wextra
LDFLAGS = -lSDL2 -lSDL2_image -ldl

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

c:
	rm -f src/*~ ./*~ include/*~

.PHONY: all clean fclean re
