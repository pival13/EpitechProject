##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	strace

SRC	=	$(wildcard *.c)

OBJ		=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Wextra -O2 -g

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	@rm -f *.o lib/*.o

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re pre_compil compil post_compil
