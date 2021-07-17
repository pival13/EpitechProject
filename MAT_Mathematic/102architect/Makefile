##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	lib/libmy.a

NAME	=	102architect

SRC2	=	lib/my_printf.c			lib/my_printf_file1.c		\
		lib/my_printf_file2.c		lib/my_str_isnum.c

SRC 	=	102architect.c			operation2.c			\
		operations.c

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Llib -lmy -Ilib -lm

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
