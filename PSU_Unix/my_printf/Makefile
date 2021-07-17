##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	libmy.a

SRC2	=	my_printf.c		my_printf_file1.c		my_printf_file2.c

OBJ2	=	$(SRC2:.c=.o)

CC	=	gcc

RM	=	rm -f

all:	$(OBJ2)
	ar rc -o $(NAME2) $(OBJ2)

clean:
	$(RM) $(OBJ2)

clean2:
	$(RM) $(OBJ2)

fclean:	clean
	$(RM) $(NAME2)

test:
	make re
	make re -Ctest
	make fclean -Ctest
	make fclean

re:	fclean all clean2

.PHONY:	all clean clean2 fclean test re
