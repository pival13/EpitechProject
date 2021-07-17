##
## EPITECH PROJECT, 2018
## Makefile of rush2
## File description:
## 
##

NAME2	=	lib/libmy.a

NAME	=	my_screensaver

SRC2	=	lib/create_framebuffer.c	lib/draw_pixel.c		\
		lib/draw_line.c			lib/draw_circle.c		\
		lib/change_color.c		lib/create_struct_window.c	\
		lib/my_strcmp.c			lib/my_str_isnum.c		\
		lib/my_printf.c			lib/my_printf_file1.c		\
		lib/my_printf_file2.c		lib/my_getnbr.c			\
		lib/draw_bloc.c			lib/move_screen.c		\
		lib/light_dissolve.c

SRC 	=	main.c				main2.c 			\
		screensaver1.c			screensaver2.c			\
		screensaver3.c			screensaver4.c			\
		screensaver5.c			screensaver6.c			

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-lcsfml-graphics -lm -Llib -lmy -Ilib -g -Ilib

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
