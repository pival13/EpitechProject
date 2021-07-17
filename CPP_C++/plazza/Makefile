##
## EPITECH PROJECT, 2020
## CCP_plazza_2019 [WSL: Ubuntu]
## File description:
## Makefile
##

NAME	=	plazza

SRC	=	$(wildcard *.cpp) $(wildcard kitchen/*.cpp) $(wildcard reception/*.cpp) $(wildcard IPC/*.cpp)

OBJ =	$(SRC:.cpp=.o)

CXX	=	g++

CXXFLAGS	=	-iquote . -g

LDFLAGS	=	-pthread

%.o:	%.cpp
	@echo -n "\e[1;33m"$@:"\e[0m\t"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(OBJ)
	@echo -n "\e[1;35m"$(NAME):"\e[0m\t"
	$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all