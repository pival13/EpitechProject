/*
** EPITECH PROJECT, 2020
** Created by theo on 12/05/2020.
** File description:
** client_node.c
*/

#include "rfc_ia.h"

game_part_t *client_init_game_second(game_t *game,
    game_part_t *game_part, int fd)
{
    game_part->cooldown = 0;
    game_part->is_egg = NOT;
    if (fd == -1) {
        game_part->cooldown = 600;
        game_part->is_egg = IS;
    }
    game_part->orientation = 1;
    game_part->orientation = (my_rand() % 4) + 1;
    game_part->posY = my_rand() % game->map->Y;
    game_part->posX = my_rand() % game->map->X;
    game_part->team = -1;
    game_part->level = 1;
    game_part->id_inc = NULL;
    game_part->cpt = 126;
    game_part->inventory[0] = 9;
    game_part->funct = NULL;
    return game_part;
}

game_part_t *client_init_game(game_t **game, char *name, int fd)
{
    game_part_t *game_part = my_malloc(sizeof(game_part_t));

    game_part = client_init_game_second(*game, game_part, fd);
    for (int i = 1; i < 7; i++) game_part->inventory[i] = 0;
    for (teams_t *teams = (*game)->teams; teams != NULL; teams = teams->next) {
        if (strcmp(teams->name, name) == 0) {
            if (teams->limit == 0 && fd != -1) {
                my_free(game_part);
                return NULL;
            }
            game_part->team = teams->nbr;
            if (fd != -1) teams->limit--;
        }
    }
    if (game_part->team == -1) {
        my_free(game_part);
        return NULL;
    }
    game_part->uuid = new_uuid();
    game_part->uuid[36] = '\0';
    return game_part;
}

player_t *add_node(game_t *game, int fd, char *name, player_t *client)
{
    player_t *tmp = my_malloc(sizeof(player_t));
    player_t *mem = client;

    tmp->fd = fd;
    tmp->game = client_init_game(&game, name, fd);
    if (tmp->game == NULL) {
        my_free(tmp);
        return NULL;
    }
    tmp->dead = false;
    tmp->response = NULL;
    tmp->pile = NULL;
    if (fd == -1)
        tmp->pile = add_command(tmp->pile, "Egg_hatch");
    tmp->buffer = NULL;
    tmp->error = NULL;
    tmp->next = NULL;
    if (game->player == NULL) return tmp;
    for (; mem->next != NULL; mem = mem->next);
    mem->next = tmp;
    return client;
}

com_pile_t *add_command(com_pile_t *pile, char *command)
{
    com_pile_t *tmp = my_malloc(sizeof(com_pile_t));
    com_pile_t *mem = pile;
    int size = my_strlen(command);

    tmp->command = my_malloc(size + 1);
    tmp->command = strncpy(tmp->command, command, size);
    tmp->command[size] = '\0';
    tmp->next = NULL;
    if (pile == NULL) {
        return tmp;
    } else {
        for (; mem->next != NULL; mem = mem->next);
        mem->next = tmp;
    }
    return pile;
}

com_pile_t *add_command_first(com_pile_t *pile, char *command)
{
    com_pile_t *tmp = my_malloc(sizeof(com_pile_t));
    com_pile_t *mem = pile;
    int size = my_strlen(command);

    tmp->command = my_malloc(size + 1);
    tmp->command = strncpy(tmp->command, command, size);
    tmp->command[size] = '\0';
    if (pile == NULL) {
        tmp->next = NULL;
        return tmp;
    }
    tmp->next = pile->next;
    mem->next = tmp;
    return pile;
}