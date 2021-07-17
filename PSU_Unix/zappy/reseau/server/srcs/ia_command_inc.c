/*
** EPITECH PROJECT, 2020
** Created by theo on 19/06/2020.
** File description:
** ia_command_inc.c
*/

#include "rfc_ia.h"

player_t *incantation_end_ret(char *command, char *id_incantation,
    player_t *client)
{
    my_free(command);
    my_free(id_incantation);
    return client;
}

game_t **incantation_end_graph(game_t **game, player_t *client,
    int level, int team_nbr)
{
    graphics_t *temp = (*game)->graph;
    char *command = my_malloc(64);
    teams_t *teams = (*game)->teams;
    int size = sprintf(command, "pie %d %d %d\n", client->game->posX,
        client->game->posY, 0);

    for (command[size] = '\0'; temp != NULL; temp = temp->next)
        temp->pile = add_command(temp->pile, command);
    if (level == 8) {
        for (; teams != NULL; teams = teams->next) {
            if (teams->nbr == team_nbr)
                break;
        }
        if (teams == NULL) return game;
        (*game)->is_end = true;
        size = sprintf(command, "seg %s\n", teams->name);
        temp = (*game)->graph;
        for (command[size] = '\0'; temp != NULL; temp = temp->next)
            temp->pile = add_command_first(temp->pile, command);
    }
    my_free(command);
    return game;
}

player_t *incantation_end_next(player_t *client, game_t **game,
    char *id_incantation, char *command)
{
    int size;
    player_t *player = (*game)->player;
    int level = 0;
    int team_nbr = 0;

    for (; player != NULL; player = player->next) {
        if (my_strcmp(player->game->id_inc, id_incantation) == 0) {
            player->game->level++;
            my_free(player->game->id_inc);
            player->game->id_inc = NULL;
            player->response = my_malloc(20);
            size = sprintf(player->response, "Current level: %d\n",
                player->game->level);
            level = player->game->level;
            player->response[size] = '\0';
            team_nbr = player->game->team;
        }
    }
    game = incantation_end_graph(game, client, level, team_nbr);
    return incantation_end_ret(command, id_incantation, client);
}

player_t *incantation_end(player_t *client, game_t **game)
{
    char *command = my_malloc(64);
    int size;
    graphics_t *temp = (*game)->graph;
    char *id_incantation = my_malloc(37);

    if (client->game->id_inc == NULL)
        return incantation_end_ret(command, id_incantation, client);
    id_incantation = strncpy(id_incantation, client->game->id_inc, 37);
    if (game_rules_incantation_end(client, *game) != NULL)
        return incantation_end_next(client, game, id_incantation, command);
    size = sprintf(command, "pie %d %d %d\n", client->game->posX,
        client->game->posY, 1);
    command[size] = '\0';
    for (; temp != NULL; temp = temp->next)
        temp->pile = add_command(temp->pile, command);
    client->response = my_malloc(4);
    client->response = my_strcpy(client->response, "ko\n");
    return incantation_end_ret(command, id_incantation, client);
}
