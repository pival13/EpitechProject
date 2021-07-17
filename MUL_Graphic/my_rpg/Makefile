##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME2	=	lib/libmy.a

NAME	=	my_rpg

SRC2	=	$(wildcard lib/*.c)				\
		$(wildcard lib/csfml/*.c)			\
		$(wildcard lib/csfml/obj_mod/*.c)		\
		$(wildcard lib/csfml/time/*.c)			\
		$(wildcard lib/csfml/sprite_mod/*.c)		\
		$(wildcard lib/csfml/animation/*.c)		\

SRC 	=	$(wildcard *.c)					\
\
		$(wildcard src/*.c)				\
		$(wildcard src/**/*.c)				\

OBJ2	=	$(SRC2:.c=.o)

OBJ	=	$(SRC:.c=.o)

CC	=	@gcc

CFLAGS	=	-Llib -lmy -lm -Iinclude -Wall -Wextra -O2 -g -lcsfml-window -lcsfml-graphics -lcsfml-system -lcsfml-audio

all:	compil run compile

compil:
	@echo -e "\e[1;36mCompilation...\e[0m"

compile:
	@echo -e "\e[1;36mCompilation completed.\e[0m"
	@(find -name "*.c" ; find -name "*.h"; find -name "Makefile" | grep -v .git) | xargs wc -l | tail -n 1 | cut -n --complement -c 1 | cut -d ' ' -f 2 | cat | tr '\n' ' ' ; echo "Lines of code."

run:	lib $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

%.o:	%.c
	@echo -e "\e[2;36m[ OK ] Compiling\e[0m" $<
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@echo -e "\e[1;36mCleaning repository...\e[0m"
	@echo -e "\e[2;36m[ OK ] Deleting OBJ files ...\e[0m" $<
	@rm -f $(OBJ) $(OBJ2) $<

fclean:	clean
	@echo -e "\e[2;36m[ OK ] Deleting binaries ...\e[0m"
	@rm -f $(NAME) $(NAME2)

re:	fclean all

lib:	$(OBJ2)
	@ar rc -o $(NAME2) $(OBJ2)

test:	all
	@./$(NAME)

.PHONY:	all clean fclean re lib
