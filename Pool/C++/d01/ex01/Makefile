##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	menger

SRC 	=	main.c	menger.c

OBJ	=	$(SRC:.c=.o)

CC	=	@gcc

CFLAGS	=	 -std=gnu11 -Wall -Wextra

all:	pre_compil compil post_compil

pre_compil:
	@echo "Compilation..."

compil: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

post_compil:
	@echo "Compilation completed"

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re lib pre_compil compil post_compil
