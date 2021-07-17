/*
** EPITECH PROJECT, 2020
** Created by theo on 12/05/2020.
** File description:
** rfc.h
*/

#ifndef SERVER_RFC_H
#define SERVER_RFC_H

#include "my.h"

typedef char * (*function)(char *cmd, game_t *game);

typedef struct s_pointeur
{
    char *flags;
    function funct;
}t_pointeur;

/* Answer */
char *map_size(char *cmd, game_t *game);
char *content_tile(char *cmd, game_t *game);
char *content_map(char *cmd, game_t *game);
char *name_team(char *cmd, game_t *game);
char *p_position(char *cmd, game_t *game);
char *p_level(char *cmd, game_t *game);
char *p_inventory(char *cmd, game_t *game);
char *time_request(char *cmd, game_t *game);
char *time_modification(char *cmd, game_t *game);

/* Question */
char *explusion(char *cmd, game_t *game);
char *broadcast(char *cmd, game_t *game);
char *start_incantation(char *cmd, game_t *game);
char *end_incantation(char *cmd, game_t *game);
char *egg_laying(char *cmd, game_t *game);
char *resource_dropping(char *cmd, game_t *game);
char *resource_collecting(char *cmd, game_t *game);
char *death(char *cmd, game_t *game);
char *egg_laying_other(char *cmd, game_t *game);
char *graph_egg_hatching(char *cmd, game_t *game);
char *connect_egg(char *cmd, game_t *game);
char *death_egg(char *cmd, game_t *game);
char *end_game(char *cmd, game_t *game);
char *message(char *cmd, game_t *game);
char *unknow_com(char *cmd, game_t *game);
char *commmand_param(char *cmd, game_t *game);
char *connect_player(char *cmd, game_t *game);
char *all_player(char *cmd, game_t *game);
char *end_game_graph(char *cmd, __attribute__((unused))game_t *game);

#endif //SERVER_RFC_H
