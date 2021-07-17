cmake_minimum_required(VERSION 3.16)
project(server)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(server
        include/my.h
        include/rfc.h
        include/rfc_ia.h
        srcs/main.c
        srcs/client_node.c
        srcs/ia_commands.c
        srcs/graphicals_com.c
        srcs/my_tab.c
        srcs/tools.c
        srcs/look.c
        srcs/init_map.c
        srcs/server.c
        srcs/init_serv.c
        srcs/server_send.c
        srcs/death_player.c
        srcs/create_ia.c
        srcs/graphs.c
        srcs/free_game.c
        srcs/remove_node.c
        srcs/graphs_egg.c
        srcs/graph_players.c
        srcs/graph_init.c
        srcs/graph_other.c
        srcs/serv_tools.c
        srcs/server_read_graph.c
        srcs/server_read_ia.c
        srcs/game_gestion.c
        srcs/remove_player.c
        srcs/remove_graph.c
        srcs/ia_command_basic.c
        srcs/ia_command_takeset.c
        srcs/ia_command_inv.c
        srcs/ia_command_fork.c
        srcs/ia_command_other.c
        srcs/ia_command_inc.c
        srcs/gest_node.c
        srcs/node_tools.c
        srcs/game_rules.c
        srcs/graph_times.c
        srcs/other_tools.c
        srcs/look_tools.c
        Makefile)
