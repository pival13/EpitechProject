##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	lib/libmy.a

NAME	=	my_ls

SRC2	=	lib/my_printf/my_printf.c	lib/my_printf/my_printf_file1.c		\
		lib/my_printf/my_printf_file2.c	lib/my_merge_3.c			\
		lib/my_sort_list.c		lib/my_sort_list_t.c			\
		lib/my_strcmp.c			lib/my_strdup.c				\
		lib/count_nb_file.c

SRC 	=	main.c				my_ls.c					\
		write_detail.c

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Llib -lmy -Ilib -Ilib/my_printf -Wall -Wextra -O2 -g

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
