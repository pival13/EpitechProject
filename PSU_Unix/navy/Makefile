##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME2	=	lib/libmy.a

NAME	=	navy

SRC2	=	lib/get_next_line.c		lib/my_printf/my_printf.c		\
		lib/my_printf/my_printf_1.c	lib/my_printf/my_printf_2.c		\
		lib/my_getnbr.c			lib/my_getfloat.c			\
		lib/my_strlen.c			lib/str_add.c				\
		lib/my_print_array.c		lib/is_int.c				\
		lib/my_putstr.c

SRC 	=	send_signal.c			get_signal.c				\
		game.c				read_file.c				\
		main.c				array.c					\
		print_navy.c			order.c					\
		get_other_pid.c			is_end.c				\
		enemy_attack.c			answer.c

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Llib -lmy -Ilib -Wall -Wextra -O2 -g

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
