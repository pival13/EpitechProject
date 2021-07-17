##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile of lem-in
##

NAME	=	lem_in

SRC	=	main.c			create_list.c		\
		find_room.c		is_something.c		\
		create_lemin_t.c	check_input.c		\
		check_input_cpy.c	check_input_room.c	\
		create_way.c		count_args.c			\
		is_something_ci.c   find_size.c				\
\
		$(wildcard lib/*.c)

OBJ	=	$(SRC:.c=.o)

CC	=	@gcc

CFLAGS	=	-g -O2 -Ilib/include

all:	compil run compile

compil:
	@echo "Compilation..."

compile:
	@echo "Compilation completed"

run:	$(OBJ)
	@gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

test:
	@make -Ctests

re:	fclean all

.PHONY:	all clean fclean re
