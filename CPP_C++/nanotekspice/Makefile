##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	nanotekspice

SRC 	=	$(wildcard *.cpp) $(wildcard Component/*.cpp)

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++

CXXFLAGS	=	-Wall -Wextra -O2 -pipe

%.o:	%.cpp
	@echo -n "\e[1;33m"$@:"\e[0m\t"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all:	$(NAME)

$(NAME):	$(OBJ)
	@echo -n "\e[1;34m"$(NAME)"\e[0m\t"
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ) $(OBJ2)

fclean:	clean
	@rm -f $(NAME) $(NAME2)

re:	fclean all

.PHONY:	all clean fclean re lib
