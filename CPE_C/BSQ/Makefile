##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	lib/libmy.a

NAME	=	bsq

SRC2	=	lib/my_putchar.c	lib/my_putstr.c		\
		lib/my_getnbr.c		lib/my_strlen.c		\
		lib/my_str_isnum.c	lib/my_strcat.c

SRC 	=	find_biggest_square.c	is_square_of_size.c	\
		load_2d_arr_from_file.c	load_file_in_memory.c

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Llib -lmy -Ilib -g

all:	$(OBJ2) $(OBJ)
	ar rc -o $(NAME2) $(OBJ2) 
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ) $(OBJ2)

clean2:
	$(RM) $(OBJ) $(OBJ2)

fclean:	clean
	$(RM) $(NAME) $(NAME2)

re:	fclean all clean2

.PHONY:	all clean clean2 fclean re
