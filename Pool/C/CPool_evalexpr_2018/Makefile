##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## Make eval_expr
##

NAME2	=	lib/libmy.a

NAME	=	eval_expr

SRC2	=	lib/my_put_nbr.c		lib/my_putchar.c		\
		lib/my_putstr.c			lib/my_strcat.c			\
		lib/my_strlen.c			lib/my_strcmp.c			\
		lib/my_strncmp.c		lib/my_strncat.c		\
		lib/my_strncpy.c		lib/my_strcpy.c			\
		lib/my_getnbr_base.c		lib/convert_base.c

SRC 	=	main.c				eval_expr_copie.c			\
		my_rev_list.c			operation_copie.c			\
		../infin_div/infin_div.c	../infin_mult/infin_mult.c	\
		../infin_mult/make_mult.c	../infin_add/infin_add.c	\
		../infin_add/file1.c		../infin_add/file2.c		\
		../infin_mod/infin_mod.c

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
