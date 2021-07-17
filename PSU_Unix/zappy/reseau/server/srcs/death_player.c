/*
** EPITECH PROJECT, 2020
** Created by theo on 08/06/2020.
** File description:
** death_player.c
*/

#include "my.h"

player_t *death_player(game_t **game, player_t *mem)
{
    teams_t *teams = (*game)->teams;
    for (; teams != NULL; teams = teams->next) {
        if (teams->nbr == mem->game->team)
            break;
    }
    if (mem->game->is_egg == NOT)
        teams->limit++;
    mem->pile = add_command_first(mem->pile, "death");
    return mem;
}

player_t *death_ia(player_t *client, game_t **game)
{
    (*game)->graph = graph_command_death((*game)->graph, client);
    client->response = my_malloc(6);
    client->response = my_strcpy(client->response, "dead\n");
    return client;
}

game_t *check_dead(game_t *game)
{
    player_t *players = game->player;
    teams_t *teams = game->teams;

    for (player_t *tmp = NULL; players != NULL;) {
        if ((players->dead == true && players->response == NULL)
        || game->is_end) {
            printf("disconnect player: %d\n", players->fd);
            tmp = players->next;
            if (players->game->is_egg == NOT) {
                for (; teams != NULL; teams = teams->next) {
                    if (teams->nbr == players->game->team) break;
                }
                teams->limit++;
            }
            FD_CLR(players->fd, &(game->read_fds));
            game->player = remove_player(game->player, players->fd);
            players = tmp;
        }
        else players = players->next;
    }
    return game;
}