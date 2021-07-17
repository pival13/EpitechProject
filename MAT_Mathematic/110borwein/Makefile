##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

NAME	=	110borwein

SRC	=	$(wildcard *.c)		\
\
		$(wildcard lib/*.c)	\

OBJ	=	$(SRC:.c=.o)

CC	=	@gcc

CFLAGS	=	-g -O2 -I./include -lm

all:	compil run compile

compil:
	@echo "Compilation..."

compile:
	@echo "Compilation completed."

run:	$(OBJ)
	@gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

test:
	@make -Ctests

re:	fclean all

.PHONY:	all clean fclean re
