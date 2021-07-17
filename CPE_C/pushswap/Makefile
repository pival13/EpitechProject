##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	lib/libmy.a

NAME	=	push_swap

SRC2	=	lib/my_getnbr.c		lib/my_str_isnum.c	\
		lib/my_putchar.c	lib/my_putstr.c		\
		lib/my_put_nbr.c	lib/my_rev_list.c	

SRC 	=	pushswap.c		ope_pushswap.c		\
		mini_ope_pushswap.c	other_funct.c

SRC0	=	main.c

SRCB	=	bonus/main_bonus.c

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

OBJ0	=	$(SRC0:.c=.o)

OBJB	=	$(SRCB:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Llib -lmy -Ilib -Wall -Wextra -O2

all:	$(OBJ2) $(OBJ) $(OBJ0)
	ar rc -o $(NAME2) $(OBJ2) 
	$(CC) -o $(NAME) $(OBJ) $(OBJ0) $(CFLAGS)

clean:
	$(RM) $(OBJ) $(OBJ2) $(OBJ0) $(OBJB)

clean2:
	$(RM) $(OBJ) $(OBJ2) $(OBJ0)

fclean:	clean
	$(RM) $(NAME) $(NAME2)

re:	fclean all clean2

bonus:	$(OBJ2) $(OBJ) $(OBJB)
	ar rc -o $(NAME2) $(OBJ2)
	$(CC) -o $(NAME) $(OBJ) $(OBJB) $(CFLAGS)
	make clean

.PHONY:	all clean clean2 fclean re
