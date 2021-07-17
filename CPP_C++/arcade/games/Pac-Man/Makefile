##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	pacman

LIBNAME	=	lib_arcade_$(NAME).so

SRC 	=	$(wildcard *.cpp) $(wildcard ../../src/*.cpp)

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++

CXXFLAGS	=	-Wall -Wextra -O2 -fPIC -iquote ../../include

%.o:	%.cpp
	@echo -n "\e[1;33m"$@:"\e[0m\t"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(LIBNAME):	$(OBJ)
	@echo -n "\e[1;34m"$(LIBNAME)"\e[0m\t"
	$(CXX) -o $(LIBNAME) $(OBJ) $(CXXFLAGS) -shared

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(LIBNAME)

re:	fclean all

.PHONY:	all clean fclean re
