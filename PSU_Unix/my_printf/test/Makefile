##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	../tests

SRC2	=	test.c		test2.c

OBJ2	=	$(SRC2:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-L../ -lmy -lcriterion

all:	$(OBJ2)
	$(CC) -o $(NAME2) $(OBJ2) $(CFLAGS)
	./$(NAME2)

clean:
	$(RM) $(OBJ2)

clean2:
	$(RM) $(OBJ2)

fclean:	clean
	$(RM) $(NAME2)

re:	fclean all clean2

.PHONY:	all clean clean2 fclean re
