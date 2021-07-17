/*
** EPITECH PROJECT, 2020
** Created by theo on 19/06/2020.
** File description:
** ia_command_fork.c
*/

#include "rfc_ia.h"

game_t **foek_client_graph(player_t *client, game_t **game, player_t *mem)
{
    char *command = my_malloc(126);
    graphics_t *temp = (*game)->graph;
    int size = sprintf(command, "enw %s %s %d %d\n", mem->game->uuid,
        client->game->uuid, client->game->posX,
        client->game->posY);

    command[size] = '\0';
    for (; temp != NULL; temp = temp->next)
        temp->pile = add_command(temp->pile, command);
    my_free(command);
    return game;
}

player_t *fork_client(player_t *client, game_t **game)
{
    teams_t *teams = (*game)->teams;
    player_t *mem = NULL;

    for (; teams != NULL; teams = teams->next) {
        if (teams->nbr == client->game->team) break;
    }
    if (teams == NULL) return client;
    (*game)->player = add_node(*game, -1, teams->name, (*game)->player);
    mem = (*game)->player;
    for (; mem->next != NULL; mem = mem->next);
    mem->game->posY = client->game->posY;
    mem->game->posX = client->game->posX;
    game = foek_client_graph(client, game, mem);
    client->response = my_malloc(4);
    client->response = my_strcpy(client->response, "ok\n");
    return client;
}

player_t *egg_hatching(player_t *client, game_t **game)
{
    char *command = my_malloc(64);
    int size = sprintf(command, "eht %s\n", client->game->uuid);
    graphics_t *temp = (*game)->graph;

    client->game->is_egg = WAS;
    command[size] = '\0';
    for (; temp != NULL; temp = temp->next)
        temp->pile = add_command(temp->pile, command);
    my_free(command);
    return client;
}
