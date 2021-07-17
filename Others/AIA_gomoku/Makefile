AME	=  pbrain-gomoku-ai

CC	= g++

RM	= rm -f

SRCS	= $(wildcard *.cpp)

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = 
CPPFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
