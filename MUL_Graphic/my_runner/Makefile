##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	lib/libmy.a

NAME	=	my_runner

SRC2	=	lib/my_strlen.c			lib/my_putstr.c			\
		lib/get_next_line.c		lib/my_strcmp.c

SRC 	=	main.c				move_sprite.c			\
		check_end.c			jump_chara.c			\
		destroy.c			create_struct_window.c		\
		ground.c			menu.c				\
		create_struct_text.c		page.c
		
OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-lcsfml-graphics -lcsfml-system -lcsfml-audio -Llib -lmy -Ilib -Wall -Wextra -O2 -g

all:	$(NAME)

$(NAME):	lib $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ) $(OBJ2)

clean2:
	$(RM) $(OBJ2) $(OBJ)

fclean:	clean
	$(RM) $(NAME) $(NAME2)

re:	fclean all clean2

lib:	$(NAME2)

$(NAME2):	$(OBJ2)
	ar rc -o $(NAME2) $(OBJ2)

.PHONY:	all clean clean2 fclean re lib
