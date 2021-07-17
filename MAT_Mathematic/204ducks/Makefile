##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	funct

SRC 	=	funct.c

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Wextra -O2 -lm

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)
	cp 204ducks.sh 204ducks
	chmod +x 204ducks

clean:
	@rm -f $(OBJ) $(OBJ2)

fclean:	clean
	@rm -f $(NAME) $(NAME2)

re:	fclean all

.PHONY:	all clean fclean re
