##
## EPITECH PROJECT, 2018
## Makefile DOOP
## File description:
## Makefile for DOOP
##

CC	 =	gcc

SRC	=	main.c 		\
		101pong.c

OBJ	=	$(SRC:.c=.o)

NAME	=	101pong

all: $(NAME)

$(NAME):
	make -C./lib/my && make clean -C./lib/my
	$(CC) -g -o $(NAME) $(SRC) -lm -L./lib/my -lmy -I./include/

clean:
	make clean -C./lib/my
	rm -f $(OBJ)

fclean: clean
	make fclean -C./lib/my
	rm -f $(NAME) game

bonus:	
	$(CC) -o game bonus/breakout_csfml/breakout_c.c -lcsfml-graphics -lcsfml-audio -Llib/my -lmy -Iinclude

re:	fclean all bonus

.PHONY: all clean fclean bonus
