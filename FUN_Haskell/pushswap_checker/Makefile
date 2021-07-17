##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	pushswap_checker

SRC 	=	pushswap_checker.hs

CC	=	@ghc

CFLAGS	=	

all:	pre_compil compil post_compil

pre_compil:
	@echo "Compilation..."

compil:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS)

post_compil:
	@echo "Compilation completed"

clean:
	@rm -f *.hi *.o

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re lib pre_compil compil post_compil
