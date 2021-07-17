##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	libmy_malloc.so

SRC 	=	$(wildcard *.c)

OBJ	=	$(SRC:.c=.o)

CC	=	@gcc

CFLAGS	=	-fPIC -Wall -Wextra -O2 -g

all:	pre_compil compil post_compil

pre_compil:
	@echo "Compilation..."

compil:	$(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ)

post_compil:
	@echo "Compilation completed"

clean:
	@rm -f $(OBJ) $(OBJ2)

fclean:	clean
	@rm -f $(NAME) $(NAME2)

re:	fclean all

.PHONY:	all clean fclean re lib pre_compil compil post_compil
