/*
** EPITECH PROJECT, 2020
** Created by theo on 12/05/2020.
** File description:
** ia_commands.c
*/

#include "rfc_ia.h"

static t_ptr_ia tab[] = {
    {"Forward", 7, &forward},
    {"Right", 7, &right},
    {"Left", 7, &left},
    {"Look", 7, &look},
    {"Take", 7, &take},
    {"Set", 7, &drop},
    {"Inventory", 7, &inventory},
    {"Broadcast", 7, &broadcast},
    {"Connect_nbr", 0, &connect_nbr},
    {"Fork", 42, &fork_client},
    {"Egg_hatch", 0, &egg_hatching},
    {"Incantation", 0, &incantation_start},
    {"End Incantation", 300, &incantation_end},
    {"start", 0, &start_send},
    {"message", 0, &message},
    {"unknow", 0, &unknow_command},
    {"death", 0, &death_ia},
    {"Longer", 0, &buffer_error},
    {"Eject", 7, &eject},
    {NULL, 0, NULL},
};

static int eject_tab[4][4] = {
    {5, 3, 1, 7},
    {3, 1, 7, 5},
    {1, 7, 5, 3},
    {7, 5, 3, 1}
};

player_t *eject(player_t *client, game_t **game)
{
    player_t *mem = (*game)->player;
    int X = client->game->posX;
    int Y = client->game->posY;
    int ori = client->game->orientation;
    int info = 0;
    char *command;

    for (; mem != NULL; mem = mem->next) {
        if (mem->game->posX == X && mem->game->posY == Y
        && client->fd != mem->fd) {
            (ori == 1)?mem->game->posY--:(ori == 2)?mem->game->posX++:
            (ori == 3)?mem->game->posY++:mem->game->posX--;
            if (mem->game->posX == -1) mem->game->posX += (*game)->map->X;
            if (mem->game->posY == -1) mem->game->posY += (*game)->map->Y;
            info = eject_tab[ori - 1][mem->game->orientation - 1];
            command = malloc(8);
            command = strcpy(command, "start ");
            command = my_strcat(command, int_to_char(info));
            mem->pile = add_command_first(mem->pile, command);
            free(command);
            (*game)->graph = graph_command_forward((*game)->graph, mem);
        }
    }
    if (info == 0) {
        client->response = malloc(4);
        client->response = strcpy(client->response, "ko\n");
    } else {
        client->response = malloc(4);
        client->response = strcpy(client->response, "ok\n");
        command = malloc(64);
        sprintf(command, "pex %s", client->game->uuid);
        (*game)->graph->pile = add_command((*game)->graph->pile, command);
        free(command);
    }
    return client;
}

game_t **incantation_start_next(game_t **game, int const *incant,
    char *id, char *buffer)
{
    for (player_t *tmp = (*game)->player; tmp != NULL; tmp = tmp->next) {
        for (int i = 0; i < 6; i++) {
            if (tmp->fd == incant[i]) {
                tmp->game->id_inc = my_malloc(38);
                tmp->game->id_inc = strncpy(
                    tmp->game->id_inc, id, 37);
                buffer = strcat(buffer, " ");
                buffer = strcat(buffer, tmp->game->uuid);
                tmp->response = my_malloc(21);
                tmp->response = my_strcpy(tmp->response,
                        "Elevation underway\n");
            }
        }
    }
    return game;
}

player_t *incantation_start_ret(char *id, int *incanter, char *buffer,
    player_t *client)
{
    my_free(buffer);
    my_free(incanter);
    my_free(id);
    return client;
}

player_t *incantation_start(player_t *client, game_t **game)
{
    char *buffer = my_malloc(1024);
    int size;
    char *id = new_uuid();
    int *incanter = game_rules_incantation_start(client, *game);

    if (incanter == NULL) {
        client->response = my_malloc(4);
        client->response = my_strcpy(client->response, "ko\n");
    } else {
        size = sprintf(buffer, "pic %d %d %d", client->game->posX,
            client->game->posY, client->game->level);
        buffer[size] = '\0';
        game = incantation_start_next(game, incanter, id, buffer);
        buffer = my_charcat(buffer, '\n');
        for (graphics_t *t = (*game)->graph; t != NULL; t = t->next)
            t->pile = add_command(t->pile, buffer);
        client->pile = add_command_first(client->pile, "End Incantation\n");
    }
    return incantation_start_ret(id, incanter, buffer, client);
}

graphics_t *graph_call_animation(game_t *game, player_t *client, char *command)
{
    int size;
    graphics_t *temp = game->graph;
    char *buffer = my_malloc(1024);

    if (strncmp("Fork", command, 4) == 0) {
        size = sprintf(buffer, "pfk %s\n", client->game->uuid);
        buffer[size] = '\0';
        for (; temp != NULL; temp = temp->next)
            temp->pile = add_command(temp->pile, buffer);
    }
    my_free(buffer);
    return game->graph;
}

player_t *ia_command(game_t **game, player_t *mem)
{
    for (int i = 0; tab[i].flags != NULL; i++) {
        if (strncmp(tab[i].flags, mem->pile->command,
            my_strlen(tab[i].flags)) == 0) {
            mem->game->cooldown = tab[i].cd;
            mem->game->funct = tab[i].funct;
            (*game)->graph = graph_call_animation(*game, mem,
                mem->pile->command);
            return mem;
        }
    }
    mem->game->cooldown = 0;
    mem->game->funct = tab[15].funct;
    return mem;
}