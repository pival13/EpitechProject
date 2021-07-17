SRC	=	$(wildcard *.cpp)

OBJ	=	$(SRC:.cpp=.o)

all: $(OBJ)
	g++ *.o -o 207demography 

clean:
	rm -f *.o

fclean: clean
	rm -f 207demography

re: fclean all