##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	arcade

SRC 	=	$(wildcard *.cpp) $(wildcard src/lib/*.cpp) src/ArcadeEvent.cpp

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++

CXXFLAGS	=	-Wall -Wextra -O2 -ldl -iquote include -fPIC -lpthread -g

%.o:	%.cpp
	@echo -n "\e[1;33m"$@:"\e[0m\t"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all:	core games graphicals

core: $(NAME)

$(NAME):	$(OBJ)
	@echo -n "\e[1;34m"$(NAME)"\e[0m\t"
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

games:
	@make --no-print-directory -C games
	@mv games/lib_arcade_MainMenu.so .

graphicals:
	@make --no-print-directory -C lib

clean:
	@rm -f $(OBJ)
	@make clean --no-print-directory -C lib
	@make clean --no-print-directory -C games

fclean:	clean
	@rm -f $(NAME) lib_arcade_MainMenu.so
	@make fclean --no-print-directory -C lib
	@make fclean --no-print-directory -C games

re:	fclean all

.PHONY:	all clean fclean re core games graphicals
