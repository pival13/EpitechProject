/*
** EPITECH PROJECT, 2020
** Created by theo on 30/04/2020.
** File description:
** my.h
*/

#ifndef PSU_ZAPPY_2019_MY_H
#define PSU_ZAPPY_2019_MY_H

/// Lib includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <uuid/uuid.h>
#include <math.h>

#include "struct.h"

#define IP "127.0.0.1"

///Server
game_t *server_read_graphics(game_t *game);
game_t *server_read_ia(game_t *game);
int server_start(game_t game);
game_t *server_send_ia(game_t *game);
game_t *server_send_graphics(game_t *game);
game_t *server_send_clients(game_t *game);
int server_loop(game_t *game);
char *longer(char *cmd, game_t *game);

///gestion game
game_t *time_gestion(game_t *game);
game_t *game_gestion(game_t *game);
game_t *gest_food(game_t *game);
game_t **new_player(game_t **game, player_t *player);
game_t **new_player_egg(game_t **game, player_t *player);
int init_games(int ac, char **av);
void free_game(game_t *game);
game_t *create_ia(game_t **game, client_t **mem);
player_t *death_player(game_t **game, player_t *mem);
tile_t **init_map(game_t game);
player_t *game_rules_incantation_end(player_t *client, game_t *game);
int *game_rules_incantation_start(player_t *client, game_t *game);
game_t *check_dead(game_t *game);

///command
player_t *ia_command(game_t **game, player_t *mem);
char *graphics_command(game_t *game, char *buffer);
graphics_t *graph_command_death(graphics_t *graph, player_t *client);
com_pile_t *add_command(com_pile_t *pile, char *command);
com_pile_t *add_command_first(com_pile_t *pile, char *command);
com_pile_t *remove_command(com_pile_t *pile);
graphics_t *graph_command_forward(graphics_t *graph, player_t *client);

///look
char *check_case(int X, int Y, game_t *game);
char *look_the_north(player_t *client, game_t *game);
char *look_the_east(player_t *client, game_t *game);
char *look_the_south(player_t *client, game_t *game);
char *look_the_west(player_t *client, game_t *game);

///list
player_t *add_node(game_t *game, int fd, char *name, player_t *client);
player_t *remove_player(player_t *list, int my_fd);
teams_t *add_teams(teams_t *teams, char *name, int nbr);
teams_t *init_teams(teams_t *teams, int clientnb);
graphics_t *add_graphs(graphics_t *graphs, int fd);
graphics_t *remove_graphs(graphics_t *list, int my_fd);
teams_t *remove_teams(teams_t *teams, int nbr);
game_t *server_add_new_client(game_t *game, int listener);
client_t *remove_new_client(client_t *list, int new_fd);
game_t *server_read_clients(game_t *game);

///tools
bool is_end(bool i);
char **my_tab(char const *buffer, char c);
int my_getnbr(char const *str);
char *int_to_char(int nbr);
void free_tab(char **tab);
char *my_charcat(char *res, char ret);
char *my_strcat_second(char *res, char *ret);
int my_strcmp(char *str, char *dest);
char *new_uuid(void);
int my_rand(void);
char *my_strcpy(char *dest, char const *src);
char *my_strcat(char *res, char *ret);
int my_strlen(const char *str);
int size_tab(char **tab);
int find_angle(player_t *client, player_t *players, map_t *map);

///memory leaks
void *my_malloc(int size);
void my_free(void *ptr);

#endif //PSU_ZAPPY_2019_MY_H