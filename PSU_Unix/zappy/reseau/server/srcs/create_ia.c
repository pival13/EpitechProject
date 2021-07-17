/*
** EPITECH PROJECT, 2020
** Created by theo on 08/06/2020.
** File description:
** create_ia.c
*/

#include "my.h"

player_t *check_egg(game_t *game, client_t *client, player_t *player)
{
    player_t *mem = player;
    teams_t *teams = game->teams;

    for (; teams != NULL; teams = teams->next) {
        if (strcmp(teams->name, client->buffer) == 0)
            break;
    }
    if (teams == NULL)
        return NULL;
    for (; mem != NULL; mem = mem->next) {
        if (mem->fd == -1 && mem->game->team == teams->nbr)
            break;
    }
    if (mem == NULL)
        return NULL;
    mem->fd = client->fd;
    return player;
}

game_t **game_create_ia(game_t **game, int new_fd, char *buffer, player_t *tmp)
{
    char *clientnum = my_malloc(42);
    int rest = 0;

    (*game)->player = tmp;
    for (tmp = (*game)->player; tmp != NULL; tmp = tmp->next)
        if (tmp->fd == new_fd) break;
    for (teams_t *team = (*game)->teams; team != NULL; team = team->next) {
        if (strcmp(team->name, buffer) == 0)
            rest = team->limit;
    }
    memset(clientnum, 0, 42);
    sprintf(clientnum, "start %d\n", rest);
    tmp->pile = add_command(tmp->pile, clientnum);
    memset(clientnum, 0, 42);
    sprintf(clientnum, "start %d %d\n", (*game)->map->X, (*game)->map->X);
    tmp->pile = add_command(tmp->pile, clientnum);
    game = new_player(game, tmp);
    my_free(clientnum);
    return game;
}

game_t **game_create_egg(game_t **game, player_t *tmp, int new_fd)
{
    char *clientnum = my_malloc(42);
    int rest = 0;

    (*game)->player = tmp;
    for (tmp = (*game)->player; tmp != NULL; tmp = tmp->next)
        if (tmp->fd == new_fd) break;
    memset(clientnum, 0, 42);
    sprintf(clientnum, "start %d\n", rest);
    tmp->pile = add_command(tmp->pile, clientnum);
    memset(clientnum, 0, 42);
    sprintf(clientnum, "start %d %d\n", (*game)->map->X, (*game)->map->X);
    tmp->pile = add_command(tmp->pile, clientnum);
    game = new_player_egg(game, tmp);
    my_free(clientnum);
    return game;
}

game_t *create_ia(game_t **game, client_t **mem)
{
    player_t *tmp = NULL;

    (*mem)->response = NULL;
    (*mem)->delete = true;
    printf("create ia = %d\n", (*mem)->fd);
    if ((tmp = check_egg(*game, *mem, (*game)->player)) != NULL) {
        printf("\033[0;32m[SERVER]->create EGG\n\033[0m");
        game = game_create_egg(game, tmp, (*mem)->fd);
    } else if ((tmp = add_node(*game, (*mem)->fd, (*mem)->buffer,
        (*game)->player)) == NULL) {
        (*mem)->response = my_malloc(17);
        (*mem)->response = strcpy((*mem)->response, "Wrong Name Team\n");
        (*mem)->response[16] = '\0';
        (*mem)->delete = true;
        printf("\033[0;32m[SERVER]->Error team name client: %d\n\033[0m",
            (*mem)->fd);
    } else {
        printf("\033[0;32m[SERVER]->create AI\n\033[0m");
        game = game_create_ia(game, (*mem)->fd, (*mem)->buffer, tmp);
    }
    return *game;
}