/*
** EPITECH PROJECT, 2020
** Created by theo on 19/06/2020.
** File description:
** ia_command_takeset.c
*/

#include "rfc_ia.h"

static char *resource[7] = {
    "food\0",
    "linemate\0",
    "deraumere\0",
    "sibur\0",
    "mendiane\0",
    "phiras\0",
    "thystame\0"
};

int find_option(char *buffer)
{
    for (; *buffer != ' '; buffer++);
    buffer++;
    for (int i = 0; i < 7; i++) {
        if (strcmp(buffer, resource[i]) == 0)
            return i;
    }
    return -1;
}

player_t *take_second(player_t *client, game_t **game, int posy, int posx)
{
    tile_t **tile = (*game)->map->tiles;
    char *command = my_malloc(64);
    int size = sprintf(command, "pgt %s %d\n", client->game->uuid,
        find_option(client->pile->command));

    tile[posy][posx].resource[find_option(client->pile->command)]--;
    client->game->inventory[find_option(client->pile->command)]++;
    client->response = my_malloc(4);
    client->response = my_strcpy(client->response, "ok\n");
    command[size] = '\0';
    for (graphics_t *temp = (*game)->graph; temp != NULL; temp = temp->next)
        temp->pile = add_command(temp->pile, command);
    my_free(command);
    return client;
}

player_t *take(player_t *client, game_t **game)
{
    int posx = client->game->posX;
    int posy = client->game->posY;
    tile_t **tile = (*game)->map->tiles;

    if (tile[posy][posx].resource[find_option(client->pile->command)] >= 1)
        return take_second(client, &(*game), posy, posx);
    client->response = my_malloc(4);
    client->response = my_strcpy(client->response, "ko\n");
    return client;
}

player_t *drop_second(player_t *client, game_t **game, int posy, int posx)
{
    graphics_t *temp = (*game)->graph;
    char *command = my_malloc(64);
    int size = sprintf(command, "pdr %s %d\n",
        client->game->uuid, find_option(client->pile->command));

    (*game)->map->tiles[posy][posx].resource[
        find_option(client->pile->command)]++;
    client->game->inventory[find_option(client->pile->command)]--;
    client->response = my_malloc(4);
    client->response = my_strcpy(client->response, "ok\n");
    command[size] = '\0';
    for (; temp != NULL; temp = temp->next)
        temp->pile = add_command(temp->pile, command);
    my_free(command);
    return client;
}

player_t *drop(player_t *client, game_t **game)
{
    int posx = client->game->posX;
    int posy = client->game->posY;

    if (client->game->inventory[find_option(client->pile->command)] >= 1)
        return drop_second(client, &(*game), posy, posx);
    client->response = my_malloc(4);
    client->response = my_strcpy(client->response, "ko\n");
    return client;
}