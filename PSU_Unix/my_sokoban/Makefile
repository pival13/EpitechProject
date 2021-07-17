##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	lib/libmy.a

NAME	=	my_sokoban

SRC2	=	lib/my_putchar.c		lib/my_putstr.c			\
		lib/load_file_in_memory.c	lib/load_2d_arr_from_file.c	\
		lib/my_strlen.c			lib/my_strcat.c			\
		lib/my_strcmp.c			my_sokoban.c			\
		my_sokoban_next.c		my_sokoban_next_next.c

SRC3	=	bonus/bonus.c			bonus/bonus2.c

SRC 	=	main.c

SRC4	=	main2.c

BONUS	=	bonus/bonus.c

OBJ2	=	$(SRC2:.c=.o)

OBJ3	=	$(SRC3:.c=.o)

OBJ	=	$(SRC:.c=.o)

OBJ4	=	$(SRC4:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Llib -lmy -Ilib -lncurses -g

all:	$(OBJ2) $(OBJ)
	ar rc -o $(NAME2) $(OBJ2) 
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ) $(OBJ2) $(OBJ3) $(OBJ4)

fclean:	clean
	$(RM) $(NAME) $(NAME2)

re:	fclean all

multi:	fclean $(OBJ2) $(OBJ4)
	ar rc -o $(NAME2) $(OBJ2) 
	$(CC) -o $(NAME) $(OBJ4) $(CFLAGS)
	make clean

bonus:	fclean $(OBJ2) $(OBJ3)
	ar rc -o $(NAME2) $(OBJ2) 
	$(CC) -o $(NAME) $(OBJ3) $(CFLAGS)
	make clean

.PHONY:	all clean fclean re bonus
