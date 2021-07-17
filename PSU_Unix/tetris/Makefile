##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

NAME	=	tetris

SRC	=	$(wildcard *.c) \
		$(wildcard **/*.c)

OBJ	=	$(SRC:.c=.o)

CC	=	@gcc

CFLAGS	=	-g -O2 -I./include -lncurses -Wall -Wextra

all:	compil run compile

compil:
	@echo -e "\e[1;36mCompilation...\e[0m"

compile:
	@echo -e "\e[1;36mCompilation completed.\e[0m"

run:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
