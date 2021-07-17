/*
** EPITECH PROJECT, 2020
** Created by theo on 11/06/2020.
** File description:
** graph_players.c
*/

#include "rfc.h"

char *p_position(char *cmd, game_t *game)
{
    player_t *player = game->player;
    char *rfc = my_malloc(64);
    int size = 0;

    memset(rfc, 0, 64);
    for (; player != NULL; player = player->next) {
        if (strncmp(cmd + 4, player->game->uuid, 36) == 0) {
            size = sprintf(rfc, "ppo %s %d %d %d\n", player->game->uuid,
                player->game->posX,
                player->game->posY, player->game->orientation);
            break;
        }
    }
    if (player == NULL) {
        my_free(rfc);
        return commmand_param(cmd, game);
    }
    rfc[size] = '\0';
    return rfc;
}

char *p_level(char *cmd, game_t *game)
{
    player_t *player = game->player;
    char *rfc = my_malloc(64);
    int size = 0;

    memset(rfc, 0, 64);
    for (; player != NULL; player = player->next) {
        if (strcmp(cmd + 4, player->game->uuid) == 0) {
            size = sprintf(rfc, "plv %s %d\n", player->game->uuid,
                player->game->level);
            break;
        }
    }
    if (player == NULL) {
        my_free(rfc);
        return commmand_param(cmd, game);
    }
    rfc[size] = '\0';
    return rfc;
}

char *p_inventory(char *cmd, game_t *game)
{
    player_t *p = game->player;
    char *rfc = my_malloc(128);

    for (int size; p != NULL; p = p->next) {
        if (strcmp(cmd + 4, p->game->uuid) == 0) {
            size = sprintf(rfc, "pin %s %d %d %d %d %d %d %d %d %d\n",
                p->game->uuid, p->game->posX,
                p->game->posY, p->game->inventory[0],
                p->game->inventory[1], p->game->inventory[2],
                p->game->inventory[3], p->game->inventory[4],
                p->game->inventory[5], p->game->inventory[6]);
            rfc[size] = '\0';
            break;
        }
    }
    if (p == NULL) {
        my_free(rfc);
        return commmand_param(cmd, game);
    }
    return rfc;
}

graphics_t *graph_command_forward(graphics_t *graph, player_t *client)
{
    graphics_t *temp = graph;
    char *command = my_malloc(64);
    int size = sprintf(command, "ppo %s\n", client->game->uuid);

    command[size] = '\0';
    for (; temp != NULL; temp = temp->next)
        temp->pile = add_command(temp->pile, command);
    my_free(command);
    return graph;
}

graphics_t *graph_command_death(graphics_t *graph, player_t *client)
{
    graphics_t *temp = graph;
    char *command = my_malloc(64);
    int size = sprintf(command, "pdi %s\n", client->game->uuid);

    command[size] = '\0';
    for (; temp != NULL; temp = temp->next)
        temp->pile = add_command(temp->pile, command);
    my_free(command);
    return graph;
}
