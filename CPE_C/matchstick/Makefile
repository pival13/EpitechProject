##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	lib/libmy.a

NAME	=	matchstick

SRC2	=	lib/my_getnbr.c			lib/my_strlen.c			\
		lib/get_next_line.c		lib/my_printf/my_printf.c	\
		lib/my_printf/my_printf_1.c	lib/my_printf/my_printf_2.c	\
		lib/destroy_map.c

SRC 	=	matchstick.c			check_map.c	\
		move_ia.c			ia.c		\
		prepare_map.c

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Llib -lmy -Ilib -Wall -Wextra -O2 -g

all:	lib $(OBJ)
	$(CC) -o $(NAME) $(OBJ) main.c $(CFLAGS)

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

bonus:	lib $(OBJ)
	$(CC) -o $(NAME) $(OBJ) bonus/*.c $(CFLAGS) -lcsfml-graphics -lcsfml-system
	make clean2

.PHONY:	all clean clean2 fclean re bonus
