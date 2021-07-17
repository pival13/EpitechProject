##
## EPITECH PROJECT, 2020
## Make file
## File description:
## clean rule
##

SRC		=	$(wildcard src/*.cpp) \
			$(wildcard src/Characters/*.cpp) \
			$(wildcard src/Pages/*.cpp) \
			$(wildcard src/Pages/MainMenu/*.cpp) \

OBJ		=	$(SRC:.cpp=.o)

NAME	=	game

CXX         =	g++
CXXFLAGS    =	-fpermissive -pipe -g -std=gnu++11 -Wall -Wno-deprecated-declarations -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS 	+=	-I./include -I./src -I./src/Characters -I./src/Pages -I./src/Pages/MainMenu

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) vgcore.*

re: fclean all

.PHONY: clean re fclean all
