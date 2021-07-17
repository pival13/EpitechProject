##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## makefile
##

STACK	=	stack

NAME	=	koak
NAME2	=	koakc
PATHEXE	=	$(shell $(STACK) path --local-install-root)/bin/
CP		=	cp -f

ifeq ($(OS),Windows_NT)
	PATHEXE=$(shell $(STACK) path --local-install-root)\bin\
	NAME	=	$(NAME).exe
	NAME2	=	$(NAME2).exe
	CP=copy
endif

all:
	$(STACK) build
	$(CP) $(PATHEXE)$(NAME) .
	$(CP) $(PATHEXE)$(NAME2) .

clean:
	@-rm -f *.o *.hi
	@-rm -rf .stack-work

fclean: clean
	@-rm -f $(NAME) $(NAME2)

tests:
	$(STACK) test

re: fclean all

.PHONY: all clean fclean re