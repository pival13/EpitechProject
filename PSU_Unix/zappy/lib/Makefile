##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC	=	Exception.cpp \

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++
CXXFLAGS    =	-I./ -I../lib/include -fPIC -pipe -g -Wall

NAME	=	lib

all: $(OBJ)
	@make -C Json/ --no-print-directory

clean:
	rm -f $(OBJ)
	@make clean -C Json/ --no-print-directory

fclean: clean
	rm -rf html
	rm -rf latex
	rm -f index.html
	@make fclean -C Json/ --no-print-directory

doc:
	rm -f index.html
	doxygen Doxyfile
	ln -s html/index.html index.html

re: fclean all

.PHONY: clean re fclean all
