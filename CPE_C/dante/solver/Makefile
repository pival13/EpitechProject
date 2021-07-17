##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	solver

SRC2	=	$(wildcard bonus/*.c)

SRC 	=	$(wildcard ./*.c)

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	@gcc

CFLAGS	=	-L../lib -lmy -I../lib -Wall -Wextra -O2 -g

all:	pre_compil compil post_compil

bonus:	pre_compil compil_bonus post_compil

pre_compil:
	@echo "\e[1;36m\tSolver Compilation...\e[0m"
	@make lib -C ..

post_compil:
	@echo "\e[1;36m\tSolver Compilated\e[0m"

compil:	$(OBJ)
	$(CC) -c -o main.o main/main.c $(CFLAGS)
	$(CC) -o $(NAME) *.o $(CFLAGS)

compil_bonus: $(OBJ) $(OBJ2)
	$(CC) -o $(NAME) $(OBJ) $(OBJ2) $(CFLAGS)

clean:
	@rm -f *.o **/*.o

fclean:	clean
	@rm -f $(NAME) $(NAME2)

re:	fclean all

.PHONY:	all clean fclean re pre_compil compil post_compil compil_bonus bonus
