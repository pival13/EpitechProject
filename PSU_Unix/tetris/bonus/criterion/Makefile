##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

## Sources à tester
SRC_DIR	=	$(realpath ..)
SRC	=	$(wildcard $(SRC_DIR)/*.c)		\
		$(wildcard $(SRC_DIR)/lib/*.c)		\

## Tests unitaires
SRC_UT_DIR	=	$(realpath .)
SRC_UT	=	$(SRC_UT_DIR)/unit_tests.c \

## Les OBJ de toutes les sources
OBJ=		$(SRC:.c=.o) $(SRC_UT:.c=.o)

## Flags de compilation
CFLAGS	=	-O2 -Wall -Wextra --coverage -I../include
LDFLAGS	=	-lcriterion -lgcov -lncurses

NAME	=	unit_tests

all:		$(NAME) run

## Rule de compilation
$(NAME):	$(OBJ)
		@gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

## Rule de test
run:	$(NAME)
	@./unit_tests


## Rule pour clean le repo
clean:
	@rm -f $(OBJ)
	@find -type f -name '*.gcda' -delete
	@find -type f -name '*.gcno' -delete
fclean:	clean
	@rm -f $(NAME)

re:	fclean all
