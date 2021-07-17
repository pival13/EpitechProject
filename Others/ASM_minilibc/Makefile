##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	libasm.so

SRC 	=	$(wildcard *.s)

OBJ	=	$(SRC:.s=.o)

AS	=	nasm

ASFLAGS	=	-f elf64 -Wall -Ox

CC	=	ld

CFLAGS	=	-shared -fPIC

all:	pre_compil compil post_compil

pre_compil:
	@echo "Compilation..."

compil: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

post_compil:
	@echo "Compilation completed"

clean:
	@rm -f $(OBJ) $(OBJ2)

fclean:	clean
	@rm -f $(NAME) $(NAME2)

re:	fclean all

.PHONY:	all clean fclean re lib pre_compil compil post_compil
