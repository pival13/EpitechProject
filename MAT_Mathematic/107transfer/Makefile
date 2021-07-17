##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile
##

SRC		=	funct_rational.c		\
			count_vars.c			\
			error_management.c		\
\
			lib/my_strlen.c			\
			lib/my_getdouble.c		\

NAME		=	107transfer

all:	$(NAME)

$(NAME):
	gcc -I./include -g $(SRC) -o $(NAME)

.PHONY: clean fclean

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all
