##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC	=	$(wildcard *.cpp) $(wildcard Trantorian/*.cpp) $(wildcard littleAI/*.cpp)
SRC_MAIN =	main/main.cpp
SRC_TEST = $(wildcard automatizedTest/*.cpp)

SRC_ADD	=	$(wildcard ../*.cpp) $(wildcard ../../lib/*.cpp)

OBJ_ADD	=	$(patsubst %.c,%.o,$(SRC_ADD:.cpp=.o))

OBJ	=	$(SRC:.cpp=.o)
OBJ_MAIN	=	$(SRC_MAIN:.cpp=.o)
OBJ_TEST	=	$(SRC_TEST:.cpp=.o)

CC	=	gcc
CXX	=	g++
CXXFLAGS    =	-iquote ../ -iquote ../../lib -iquote ../../lib/include -g -Wall -Wextra
LDFLAGS	=	-L ../../lib/Json -lJson++_nonshared -pthread

NAME	=	zappy_ai

%.o:	%.c
	@echo -n "\e[1;33m"$@:"\e[0m\t"
	$(CC) $(CXXFLAGS) -c -o $@ $<

%.o:	%.cpp
	@echo -n "\e[1;33m"$@:"\e[0m\t"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: lib $(NAME)

$(NAME):	$(OBJ) $(OBJ_ADD) $(OBJ_MAIN)
	@echo -n "\e[1;35m"$(NAME):"\e[0m\t"
	$(CXX) -o $(NAME) $(OBJ) $(OBJ_ADD) $(OBJ_MAIN) $(LDFLAGS)

test:	$(OBJ) $(OBJ_ADD) $(OBJ_TEST)
	@echo -n "\e[1;35m"binTest:"\e[0m\t"
	$(CXX) -o binTest $(OBJ) $(OBJ_ADD) $(OBJ_TEST) $(LDFLAGS)

lib:
	@make libJson++.a -C ../../lib/Json --no-print-directory

clean:
	@make clean  -C ../../lib/Json --no-print-directory
	rm -f $(OBJ) $(OBJ_ADD) $(OBJ_MAIN) $(OBJ_TEST)
	rm -rf html
	rm -rf latex
	rm -f index.html

fclean: clean
	rm -f $(NAME)

doc:
	rm -f index.html
	doxygen Doxyfile
	ln -s html/index.html index.html

re: fclean all

.PHONY: clean re fclean all
