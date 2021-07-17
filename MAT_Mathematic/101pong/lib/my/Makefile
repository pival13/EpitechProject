##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## lib makefile
##

SRC	=	my_putstr.c				\
		my_putchar.c				\
		my_compute_square_root.c		\
		my_getnbr.c				\
		my_is_prime.c				\
		my_put_nbr.c				\
		my_putnbr_base.c			\
		my_revstr.c				\
		my_showmem.c				\
		my_showstr.c				\
		my_show_word_array.c			\
		my_sort_int_array.c			\
		my_strcmp.c				\
		my_strcpy.c				\
		my_str_islower.c			\
		my_str_isnum.c				\
		my_str_isprintable.c			\
		my_str_isupper.c			\
		my_strlen.c				\
		my_strlowcase.c				\
		my_strncmp.c				\
		my_strncpy.c				\
		my_strstr.c				\
		my_strupcase.c				\
		my_swap.c				\
		my_atoi.c				\
		addition.c		\
		infin_mult.c		\
		soustraction.c		\
		soustraction2.c		\
		infin_add.c		\
		multiplication.c	\
		multiplication2.c	\
		infin_sub.c		\
		infin_div.c		\
		infin_modulo.c		\
		my_erasestr.c		\
		str_add.c		\
		my_getfloat.c		\
		my_get_strtonbr.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -c $(SRC) -I../../include
	ar rc libmy.a $(OBJ)
clean:
	rm -f $(OBJ)
fclean:	clean
	rm -f $(NAME)
	rm -f libmy.a

re:	fclean all

.phony:	re fclean clean all
