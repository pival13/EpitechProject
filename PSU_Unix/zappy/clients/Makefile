##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC	=	Client.cpp \
		ClientData.cpp \
		ClientSocket.cpp \
		Tile.cpp \
		Position.cpp \
		PlayerData.cpp \
		InventoryData.cpp \
		EggData.cpp \

SRCTEST =	main.cpp \

OBJ	=	$(SRC:.cpp=.o) \

OBJADD	=	../lib/Exception.o \

CXX	=	g++
CXXFLAGS    =	-I./ -I../lib/include -fPIC -pipe -g -Wall -lpthread

all: compile
	@make -C ai/ --no-print-directory
	@make -C graphical/ --no-print-directory

compile: $(OBJ)

clean:
	rm -f $(OBJ)
	@make clean -C ai/ --no-print-directory
	@make clean -C graphical/ --no-print-directory

fclean: clean
	rm -rf html
	rm -rf latex
	rm -f index.html
	@make fclean -C ai/ --no-print-directory
	@make fclean -C graphical/ --no-print-directory

test: compile
	$(CXX) -o test $(OBJ) $(OBJADD) $(SRCTEST) $(CXXFLAGS)

doc:
	rm -f index.html
	doxygen Doxyfile
	ln -s html/index.html index.html
	@make doc -C ai/ --no-print-directory
	@make doc -C graphical/ --no-print-directory

re: fclean all

.PHONY: clean re fclean all
