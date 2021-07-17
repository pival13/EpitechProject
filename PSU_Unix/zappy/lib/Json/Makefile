##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC_C	=	$(wildcard *.c)
SRC_CPP	=	$(wildcard *.cpp)

OBJ_C =	$(patsubst %.c,%.o,$(SRC_C))
OBJ_CPP =	$(SRC_CPP:.cpp=.o)

CC	=	gcc
CXX	=	g++
CXXFLAGS    =	-Wall -Wextra -fPIC

LD	=	ld -shared
AR	=	ar rc

NAME	=	Json

%.o:	%.c
	@echo -n "\e[1;33m"$@:"\e[0m\t"
	$(CC) $(CXXFLAGS) -c -o $@ $<

%.o:	%.cpp
	@echo -n "\e[1;33m"$@:"\e[0m\t"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(OBJ_C) $(OBJ_CPP) lib$(NAME).so lib$(NAME)++.so lib$(NAME).a lib$(NAME)++.a

lib$(NAME).so:	$(OBJ_C)
	@echo -n "\e[1;36m"$@: "\e[0m\t"
	$(LD) -o $@ $(OBJ_C)

lib$(NAME)++.so:	$(OBJ_C) $(OBJ_CPP)
	@echo -n "\e[1;36m"$@: "\e[0m\t"
	$(CC) -shared -o $@ $(OBJ_C) $(OBJ_CPP)
	@#$(LD) -o $@ $(OBJ_C) $(OBJ_CPP)

lib$(NAME).a:	$(OBJ_C)
	@echo -n "\e[1;36m"$@: "\e[0m\t"
	$(AR) -o $@ $(OBJ_C)
	@echo -n "\e[1;36m"$*_nonshared.a: "\e[0m\t"
	cp $@ $*_nonshared.a

lib$(NAME)++.a:	$(OBJ_C) $(OBJ_CPP)
	@echo -n "\e[1;36m"$@: "\e[0m\t"
	$(AR) -o $@ $(OBJ_C) $(OBJ_CPP)
	@echo -n "\e[1;36m"$*_nonshared.a: "\e[0m\t"
	cp $@ $*_nonshared.a

clean:
	rm -f $(OBJ_C) $(OBJ_CPP)

fclean: clean
	rm -f lib$(NAME).a lib$(NAME)_nonshared.a lib$(NAME)++.a lib$(NAME)++_nonshared.a lib$(NAME).so lib$(NAME)++.so

re: fclean all

.PHONY: clean re fclean all