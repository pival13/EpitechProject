##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME2	=	lib/libmy.a

NAME	=	mysh

SRC2	=	$(wildcard lib/*.c)

SRC 	=	$(wildcard *.c)

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	@gcc

RM	=	@rm -f

CFLAGS	=	-Llib -lmy -Ilib -Wall -Wextra -O2 -g

all:	compil run compile

compil:
		@echo "\e[7;3mCompilation...\e[0m"

compile:
		@echo "\e[7;3mCompilation completed\e[0m"

run:	lib $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ) $(OBJ2)

fclean:	clean
	$(RM) $(NAME) $(NAME2)

re:	fclean all

lib:	$(OBJ2)
	@ar rc -o $(NAME2) $(OBJ2)

.PHONY:	all clean clean2 fclean re
