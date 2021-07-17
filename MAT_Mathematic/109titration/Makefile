##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	109titration

SRC	=	$(wildcard *.c)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc -I./include

CFLAGS	=	-Wall -Wextra -O2 -g -lm

all:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	@rm -f $(OBJ) $(OBJ2)

fclean:	clean
	@$(RM) $(NAME) $(NAME2)

re:	fclean all

.PHONY:	all clean fclean re lib
