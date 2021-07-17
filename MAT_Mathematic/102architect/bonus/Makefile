##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	lib/libmy.a

NAME	=	architect

SRC2	=	lib/create_framebuffer.c	lib/put_pixel.c			\
		lib/draw_line.c			lib/draw_circle.c		\
		lib/change_color.c		lib/create_struct_window.c	\
		lib/destroy_everything.c	lib/display_window.c

SRC 	=	architect.c

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-lcsfml-graphics -Llib -lmy -Ilib -g

all:	$(OBJ2) $(OBJ)
	ar rc -o $(NAME2) $(OBJ2)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ) $(OBJ2)

clean2:
	$(RM) $(OBJ) $(OBJ2)

fclean:	clean
	$(RM) $(NAME) $(NAME2)

re:	fclean all clean2

.PHONY:	all clean clean2 fclean re
