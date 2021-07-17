##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME2	=	lib/libmy.a

NAME	=	108trigo

SRC2	=	$(wildcard lib/*.c)

SRC3	=	$(wildcard bonus/*.c)

SRC 	=	exp_matrix.c	sin_matrix.c	cos_matrix.c	cosh_matrix.c	sinh_matrix.c

OBJ2	=	$(SRC2:.c=.o)

OBJ3	=	$(SRC3:.c=.o)

OBJ	=	$(SRC:.c=.o) \

CC	=	gcc

CFLAGS	=	-Llib -lmy -Ilib -Wall -Wextra -O2 -g -lm

all:	lib $(OBJ)
	@$(CC) -c -o main.o main.c $(CFLAGS)
	@$(CC) -o $(NAME) main.o $(OBJ) $(CFLAGS)

bonus:	lib $(OBJ) $(OBJ3)
	@$(CC) -o $(NAME) $(OBJ) $(OBJ3) $(CFLAGS)

clean:
	@rm -f $(OBJ) $(OBJ2)

fclean:	clean
	@rm -f $(NAME) $(NAME2)

re:	fclean all

lib:	$(OBJ2)
	@ar rc -o $(NAME2) $(OBJ2)

.PHONY:	all clean fclean re lib bonus
