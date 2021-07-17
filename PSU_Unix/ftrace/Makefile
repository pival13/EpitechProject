##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	ftrace

SRC	=	$(wildcard *.c) $(wildcard lib/*.c)

OBJ		=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Wextra -O2
LDFLAGS	=	-lelf

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f *.o lib/*.o

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re pre_compil compil post_compil
