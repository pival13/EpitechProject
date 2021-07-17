NAME	=	Xlib

LIBNAME	=	lib_arcade_$(NAME).so

SRC 	=	$(wildcard *.cpp) $(wildcard ../../src/*.cpp)

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++

CXXFLAGS	=	-Wall -Wextra -Ofast -fPIC -iquote ../../include -g -std=c++11
CXXFLAGS	+= -L/usr/X11R6/lib -lX11

%.o:	%.cpp
	@echo -n "\e[1;33m"$@:"\e[0m\t"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(LIBNAME):	$(OBJ)
	@echo -n "\e[1;34m"$(LIBNAME)"\e[0m\t"
	$(CXX) -o $(LIBNAME) $(OBJ) $(CXXFLAGS) $(LDFLAGS) -shared

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(LIBNAME)

re:	fclean $(LIBNAME)

.PHONY:	all clean fclean re