##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC	=	main.cpp \
		GraphicalClient.cpp \
		MainWindow.cpp \
		$(wildcard Sfml/*.cpp) \
		$(wildcard Sfml/**/*.cpp) \
		$(wildcard Pages/*.cpp) \
		$(wildcard Game/*.cpp) \
		$(wildcard Game/**/*.cpp) \
		$(wildcard Menu/*.cpp) \

SRCADD	=	$(wildcard ../*.cpp) $(wildcard ../../lib/*.cpp) \
			$(wildcard ../../lib/**/*.cpp) $(wildcard ../../lib/**/*.c)

OBJADD	=	$(patsubst %.c,%.o,$(SRCADD:.cpp=.o)) \

OBJ	=	$(SRC:.cpp=.o) \

CXX	=	g++
CXXFLAGS    =	-I./ -I../ -I../../lib/ -I../../lib/include -I./Sfml/
CXXFLAGS	+=	-I./Sfml/ResourcesDatabase/ -I./Pages/
CXXFLAGS	+=	-I./Game/ -I./Game/Mobs/ -I./Game/BottomBar/
CXXFLAGS	+=	-I./Menu/
CXXFLAGS	+=	-g -Wall -lpthread
CXXFLAGS	+=	 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

NAME	=	zappy_graphical

all: compile

compile: $(OBJ) $(OBJADD)
	$(CXX) -o $(NAME) $(OBJ) $(OBJADD) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf html
	rm -rf latex
	rm -f index.html

doc:
	rm -f index.html
	doxygen Doxyfile
	ln -s html/index.html index.html

re: fclean all

.PHONY: clean re fclean all
