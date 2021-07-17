##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME2	=	lib/libmy.a

SRC2	=	$(wildcard lib/*.c)

OBJ2	=	$(SRC2:.c=.o)

CC	=	@gcc

CFLAGS	=	-Llib -lmy -Ilib -Wall -Wextra -O2 -g

all:	solver generator

bonus:	solver_bonus generator_bonus

solver:
	@make -C solver
	@cp solver/solver ./sol

generator:
	@make -C generator
	@cp generator/generator ./gen

generator_bonus:
	@make bonus -C generator
	@cp generator/generator ./gen

solver_bonus:
	@make bonus -C solver
	@cp solver/solver ./sol

clean:
	@rm -f $(OBJ2)
	@make clean -C solver
	@make clean -C generator

fclean:	clean
	@rm -f $(NAME2) sol gen generator/generator solver/solver

re:	fclean all

lib:	$(OBJ2)
	@ar rc -o $(NAME2) $(OBJ2)

.PHONY:	all clean fclean re lib solver generator bonus
