##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile test
##

SRC=	test_create_list.c		test_printf.c		\
	test_read_file.c		../create_list.c	\
	../find_room.c			$(wildcard ../lib/*.c)

#$(wildcard ../*.c)	$(wildcard ./*.c)	$(wildcard ../lib/*.c)

OBJ=	$(SRC:.c=.o)

CFLAGS=	-Wall -Wextra --coverage -lcriterion -I../lib/include

NAME=	unit_test

all:	$(OBJ)
	@gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)
	./$(NAME)

clean:
	@rm -f $(OBJ)
	@find -type f -name '*.gcda' -delete
	@find -type f -name '*.gcno' -delete

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
