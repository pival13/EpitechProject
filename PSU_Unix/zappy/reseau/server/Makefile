NAME	= zappy_server

CC	= gcc -g

RM	= rm -f

SRCS	= ./srcs/main.c \
		./srcs/client_node.c \
		./srcs/graphicals_com.c \
		./srcs/ia_commands.c \
		./srcs/my_tab.c \
		./srcs/tools.c \
		./srcs/look.c \
		./srcs/graphs.c \
		./srcs/init_map.c \
		./srcs/init_serv.c \
		./srcs/server.c \
		./srcs/server_send.c \
		./srcs/death_player.c \
		./srcs/create_ia.c \
		./srcs/free_game.c \
		./srcs/remove_node.c \
		./srcs/graph_players.c \
		./srcs/graphs_egg.c \
		./srcs/graph_init.c \
		./srcs/graph_other.c \
		./srcs/serv_tools.c \
		./srcs/server_read_graph.c \
		./srcs/server_read_ia.c \
		./srcs/game_gestion.c \
		./srcs/remove_player.c \
		./srcs/remove_graph.c \
		./srcs/ia_command_basic.c \
		./srcs/ia_command_takeset.c \
		./srcs/ia_command_inv.c \
		./srcs/ia_command_fork.c \
		./srcs/ia_command_other.c \
		./srcs/ia_command_inc.c \
		./srcs/gest_node.c \
		./srcs/node_tools.c \
		./srcs/game_rules.c \
		./srcs/graph_times.c \
		./srcs/other_tools.c \
		./srcs/look_tools.c	\
		./srcs/ia_position.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/
CFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -luuid -lm

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
