##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	generator

SRC 	=	$(wildcard ./*.c)	$(wildcard eller/*.c)	$(wildcard hunt_kill/*.c)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-L../lib -lmy -I../lib -Wall -Wextra -O2 -g

all:	pre_compil compil post_compil

bonus:	pre_compil compil_bonus post_compil

pre_compil:
	@echo "\e[1;36m\tGenerator Compilation...\e[0m"
	@make lib -C ..

compil:	$(OBJ)
	$(CC) -c -o main.o main/main.c $(CFLAGS)
	$(CC) -o $(NAME) $(OBJ) main.o $(CFLAGS)

compil_bonus:	$(OBJ)
	$(CC) -c -o main.o bonus/main.c $(CFLAGS)
	$(CC) -o $(NAME) $(OBJ) main.o $(CFLAGS)

post_compil:
	@echo "\e[1;36m\tGenerator Compilated\e[0m"

clean:
	@rm -f *.o **/*.o

fclean:	clean
	@rm -f $(NAME) $(NAME2)

re:	fclean all

.PHONY:	all clean fclean re pre_compil compil post_compil
