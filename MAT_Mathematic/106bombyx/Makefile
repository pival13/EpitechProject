##
## EPITECH PROJECT, 2018
## Makefile DOOP
## File description:
## Makefile for DOOP
##

CC	 =	gcc

SRC	=	main.c 			\
		formula.c		\
\
		lib/load_file_in_mem.c	\
		lib/my_atoi.c		\
		lib/my_getfloat.c	\
		lib/my_getnbr.c		\
		lib/my_putstr.c		\
		lib/my_revstr.c		\
		lib/my_strlen.c		\
		lib/str_add.c		\
		lib/my_getdouble.c	\
		lib/is_int.c		\
		lib/is_float.c		\

OBJ	=	$(SRC:.c=.o)

NAME	=	106bombyx

all: $(NAME)

$(NAME):
	$(CC) -g -o $(NAME) $(SRC) -I./include -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean
