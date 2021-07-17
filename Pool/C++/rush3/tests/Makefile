##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

CXX = g++ -g

SRCMod = $(wildcard ../Modules/*.cpp)
SRCMain = $(wildcard *.cpp)

NAME = test

OBJ = $(SRCMod:.cpp=.o) $(SRCMain:.cpp=.o)

RM = rm -f

CXXFLAGS += -W -Wall -Wextra -I ..

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
