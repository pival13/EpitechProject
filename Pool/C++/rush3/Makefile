##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

CXX = g++ -g

SRCInt = $(wildcard Interfaces/*.cpp)
SRCMod = $(wildcard Modules/*.cpp)
SRCNcu = $(wildcard Ncurses/*.cpp)
SRCMain = main.cpp
#SRCSfml = $(wildcard Sfml/*.cpp)

NAME = MyGKrellm

OBJ = $(SRCInt:.cpp=.o) $(SRCMod:.cpp=.o) $(SRCMain:.cpp=.o) $(SRCNcu:.cpp=.o)# $(SRCSfml:.cpp=.o)

RM = rm -f

CXXFLAGS += -W -Wall -Wextra -lncurses# -lsfml-graphics -lsfml-system -lsfml-window

TRASH += vgcore.*
TRASH += *~
TRASH += *.o
TRASH += *.gcda
TRASH += *.gcno

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(TRASH)

re: fclean all

.PHONY: all clean fclean re
