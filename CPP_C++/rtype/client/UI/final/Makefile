NAME	= Rtype

CC	= g++

RM	= rm -f

SRCS	= $(wildcard src/*.cpp)

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -std=c++0x -Wall -Wextra -Wno-unused-parameter -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
