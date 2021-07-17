##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME2	=	lib/libmy.a

NAME	=	my_world

SRC2	=	lib/get_next_line.c		lib/my_getnbr.c			\
		lib/read_file.c

SRC 	=	main.c				create_world_t.c		\
		interaction.c			destroy.c			\
		edit_map.c			create_texture.c		\
		create_text.c			create_page.c			\
		create_map.c			event.c				\
		change_map_interaction.c	cmp_color.c

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Llib -lmy -lcsfml-graphics -lcsfml-audio -lm -Ilib -Wall -Wextra -O2 -g

all:	lib $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	@$(RM) $(OBJ) $(OBJ2)

clean2:
	@$(RM) $(OBJ2) $(OBJ)

fclean:	clean
	@$(RM) $(NAME) $(NAME2)

re:	fclean all clean2

lib:	$(OBJ2)
	@ar rc -o $(NAME2) $(OBJ2)
	@make clean2

.PHONY:	all clean clean2 fclean re
