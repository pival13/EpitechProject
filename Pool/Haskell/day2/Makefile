##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	doop

SRC 	=	DoOp.hs

CC	=	@ghc

all:	pre_compil compil post_compil

pre_compil:
	@echo "Compilation..."

compil:
	$(CC) -o $(NAME) $(SRC)

post_compil:
	@echo "Compilation completed"

clean:
	@rm -f *.o *.hi

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re lib pre_compil compil post_compil
