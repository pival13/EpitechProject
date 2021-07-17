##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

NAME	=	corewar

CC	= @gcc

RM	= @rm -f

SRCS	= 	$(wildcard *.c) 											\
			$(wildcard src/**/*.c)

OBJS	= $(SRCS:.c=.o)

CFLAGS	=	-L../lib -lmy -I./include -Wall -Wextra -O2 -g

all: pre_compil $(NAME) post_compil

##tests_run:
##				cd tests/ && $(MAKE)

pre_compil:
	@echo -e "\e[1;36m\tVirtual Machine Compilation...\e[0m"
	@make lib -C ..

post_compil:
	@echo -e "\e[1;36m\tVirtual Machine Compilated\e[0m"

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
