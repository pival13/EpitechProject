##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	lib/libmy.a

NAME	=	105torus

SRC2	=	lib/my_str_isfloat.c	lib/my_str_isint.c

SRC 	=	main.c			bissection.c		\
		newton.c		secant.c

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Llib -lmy -Ilib -Wall -Wextra -O2 -g -lm

all:	lib $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ) $(OBJ2)

clean2:
	$(RM) $(OBJ2) $(OBJ)

fclean:	clean
	$(RM) $(NAME) $(NAME2)

re:	fclean all clean2

lib:	$(OBJ2)
	ar rc -o $(NAME2) $(OBJ2)
	make clean2	

.PHONY:	all clean clean2 fclean re
