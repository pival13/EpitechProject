##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	my_convert_temp

SRC 	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)

CXX	=	@g++

CXXFLAGS	=	-Wall -Wextra -Werror -O2 -g

all:	pre_compil compil post_compil

pre_compil:
	@echo "Compilation..."

compil: $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

post_compil:
	@echo "Compilation completed"

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re lib pre_compil compil post_compil
