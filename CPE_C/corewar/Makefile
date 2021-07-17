##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME2	=	lib/libmy.a

SRC2	=	$(wildcard lib/*.c) op.c $(wildcard lib/**/*.c)

OBJ2	=	$(SRC2:.c=.o)

CC	=	@gcc

CFLAGS	=	-Llib -lmy -Iinclude -Wall -Wextra -O2 -g

all:	assembler virtualmachine

#bonus:	solver_bonus generator_bonus

assembler:
	@make -C asm
	@cp asm/asm ./assembler

virtualmachine:
	@make -C virtualmachine
	@cp virtualmachine/corewar .

#generator_bonus:
#	@make bonus -C generator
#	@cp generator/generator ./gen
#
#solver_bonus:
#	@make bonus -C solver
#	@cp solver/solver ./sol

clean:
	@rm -f $(OBJ2)
	@make clean -C asm
	@make clean -C virtualmachine

fclean:	clean
	@rm -f $(NAME2) assembler corewar asm/asm virtualmachine/corewar

re:	fclean all

lib:	$(OBJ2)
	@ar rc -o $(NAME2) $(OBJ2)

.PHONY:	all clean fclean re lib assembler virtualmachine bonus
