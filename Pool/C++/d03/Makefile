##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	libstring.a

SRC	=	$(wildcard src/*.c)

OBJ	=	$(SRC:.c=.o)

CC 	=	@gcc

CFLAGS	=	-Wall -Wextra -g -I src

all:	pre_compil compil post_compil

pre_compil:
	@cp header/string.h .
	@rm ./string.h
	@echo "Compilation..."

compil: $(OBJ)
	@ar rc -o $(NAME) $(OBJ)

post_compil:
	@cp header/string.h .
	@echo "Compilation completed"

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

lib:	$(OBJ2)

.PHONY:	all clean fclean re lib pre_compil compil post_compil
