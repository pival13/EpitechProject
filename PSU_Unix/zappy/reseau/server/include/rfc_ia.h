/*
** EPITECH PROJECT, 2020
** Created by theo on 20/05/2020.
** File description:
** rfc_ia.h
*/

#ifndef SERVER_RFC_IA_H
#define SERVER_RFC_IA_H

#include "my.h"

typedef struct s_ptr_ia
{
    char *flags;
    int cd;
    fct funct;
} t_ptr_ia;

player_t *forward(player_t *client, game_t **game);
player_t *right(player_t *client, game_t **game);
player_t *left(player_t *client, game_t **game);
player_t *look(player_t *client, game_t **game);
player_t *take(player_t *client, game_t **game);
player_t *drop(player_t *client, game_t **game);
player_t *inventory(player_t *client, game_t **game);
player_t *broadcast(player_t *client, game_t **game);
player_t *connect_nbr(player_t *client, game_t **game);
player_t *fork_client(player_t *client, game_t **game);
player_t *egg_hatching(player_t *client, game_t **game);
player_t *incantation_end(player_t *client, game_t **game);
player_t *incantation_start(player_t *client, game_t **game);
player_t *start_send(player_t *client, game_t **game);
player_t *message(player_t *client, game_t **game);
player_t *unknow_command(player_t *client, game_t **game);
player_t *death_ia(player_t *client, game_t **game);
player_t *buffer_error(player_t *client, game_t **game);
player_t *eject(player_t *client, game_t **game);

#endif //SERVER_RFC_IA_H
