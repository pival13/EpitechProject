##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## Makefile
##

NAME	= ../zappy_server

CC	= gcc

RM	= rm -f

SRCS	= ./add_node.c \
	  ./delete/delete.c \
	  ./delete/delete_client.c \
	  ./delete/delete_map.c \
	  ./delete/delete_client_list.c \
	  ./command.c \
	  ./init.c \
	  ./main.c \
	  ./incantation.c \
	  ./end_of_game.c \
	  ./egg/egg_time_gestion.c \
	  ./egg/egg_connection.c \
	  ./egg/graphical.c \
	  ./send_answer.c \
	  ./parsing/clients_nb.c \
	  ./parsing/check_args.c \
	  ./parsing/freq.c \
	  ./parsing/height.c \
	  ./parsing/name_x.c \
	  ./parsing/pars.c \
	  ./parsing/port.c \
	  ./parsing/width.c \
	  ./parsing/pars_get_number.c \
	  ./set_server.c \
	  ./server_loop.c \
	  ./command/bct.c \
	  ./client/graphicals.c \
	  ./client/spawn_client.c \
	  ./client/client_connection.c \
	  ./client/life_gestion.c \
	  ./command/broadcast/broadcast.c \
	  ./command/broadcast/calc/calc.c \
	  ./command/broadcast/calc/find_smallest.c \
	  ./command/broadcast/send.c \
	  ./command/connect_nbr.c \
	  ./command/eject/eject.c \
	  ./command/eject/broadcast.c \
	  ./command/fork_c.c \
	  ./command/forward/forward.c \
	  ./command/forward/move.c \
	  ./command/incantation/incantation.c \
	  ./command/incantation/verify.c \
	  ./command/incantation/send_client.c \
	  ./command/incantation/prerequisite.c \
	  ./command/incantation/send_invocation_client.c \
	  ./command/inventory.c \
	  ./command/left.c \
	  ./command/look.c \
	  ./command/mct.c \
	  ./command/msz.c \
	  ./command/pin.c \
	  ./command/plv.c \
	  ./command/ppo.c \
	  ./command/right.c \
	  ./command/set/set.c \
	  ./command/set/take_ressources.c \
	  ./command/sgt.c \
	  ./command/sst.c \
	  ./command/take/take.c \
	  ./command/take/take_ressources.c \
	  ./command/tna.c \
	  ./command/look_tools.c \
	  ./command_gestion/add_command.c \
	  ./command_gestion/check_command.c \
	  ./command_gestion/cooldown_gestion.c \
	  ./command_gestion/exec_command.c \
	  ./command_gestion/get_command.c \
	  ./command_gestion/handle_command.c \
	  ./command_gestion/graphicals.c \
	  ./utils_function/free_array.c \
	  ./utils_function/is_digit.c \
	  ./utils_function/my_const_strcmp.c \
	  ./utils_function/my_strcat.c \
	  ./utils_function/my_strcmp.c \
	  ./utils_function/size_array.c \
	  ./utils_function/str_to_word_array.c \
	  ./utils_function/copy_array.c \
	  ./utils_function/my_int_to_char.c \
	  ./utils_function/my_strlen.c \
	  ./utils_function/send_to_all_graphic.c \
	  ./utils_function/is_equal.c \
	  ./utils_function/max_in_teams.c \
	  ./utils_function/found_separator.c \
	  ./utils_function/how_many_in_the_team.c \
	  ./utils_function/team_name_not_found.c \
	  ./init_ressources/add_deraumere.c \
	  ./init_ressources/add_linemate.c \
	  ./init_ressources/add_mendiane.c \
	  ./init_ressources/add_phiras.c \
	  ./init_ressources/add_sibur.c \
	  ./init_ressources/add_thystame.c \
	  ./init_ressources/init_map.c \
	  ./init_ressources/refill_map.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ../lib/Json -I ./
CFLAGS += -g -Wall -Wextra

LDFLAGS = -L../lib/Json/ -lJson_nonshared

all:
	@make -C ../lib
	@make $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) $(CFLAGS) -o $(NAME) $(LDFLAGS) -lm

clean:
	$(RM) $(OBJS)

fclean: clean
	rm -rf html
	rm -rf latex
	rm -f index.html
	$(RM) $(NAME)

doc:
	rm -f index.html
	doxygen Doxyfile
	ln -s html/index.html index.html

re: fclean all

.PHONY: all clean fclean re
