##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	my_cat

SRC 	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)

CC	=	@g++

CFLAGS	=	-Wall -Wextra -Werror -O2 -g

all:	pre_compil compil post_compil

pre_compil:
	@echo "Compilation..."

compil: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

post_compil:
	@echo "Compilation completed"

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re lib pre_compil compil post_compil
