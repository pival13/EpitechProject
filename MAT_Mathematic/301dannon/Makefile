##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	301dannon

SRC 	=	301dannon.hs main.hs

CC	=	ghc

CFLAGS	=	-Wall -Wextra -O2 -g -pipe

all:	pre_compil compil post_compil

pre_compil:
	@echo "Compilation..."

compil: 
	ghc -o $(NAME) $(SRC)

post_compil:
	@echo "Compilation completed"

clean:
	@rm -f *.o *.hi

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re lib pre_compil compil post_compil