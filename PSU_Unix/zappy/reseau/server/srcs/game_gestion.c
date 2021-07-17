/*
** EPITECH PROJECT, 2020
** Created by theo on 16/06/2020.
** File description:
** game_gestion.c
*/

#include "rfc_ia.h"

game_t *gest_food(game_t *game)
{
    player_t *mem = game->player;

    for (; mem != NULL && !game->is_end; mem = mem->next) {
        if (mem->game->is_egg == IS)
            continue;
        if (mem->game->cpt <= 0 && mem->game->inventory[0] != 0) {
            mem->game->cpt = 126;
        }
        if (mem->game->inventory[0] == 0 && mem->game->cpt <= 0)
            mem = death_player(&game, mem);
    }
    return game;
}

game_t *game_gestion(game_t *game)
{
    for (player_t *play = game->player; play != NULL && !game->is_end;
    play = play->next) {
        if (play->game->cooldown <= 0) {
            if (play->game->funct != NULL) {
                play = play->game->funct(play, &game);
                play->game->funct = NULL;
                play->pile = remove_command(play->pile);
                continue;
            }
            if (play->pile == NULL)
                continue;
            play = ia_command(&game, play);
        }
    }
    for (graphics_t *graph = game->graph; graph != NULL; graph = graph->next) {
        if (graph->pile != NULL && graph->response == NULL) {
            graph->response = graphics_command(game, graph->pile->command);
            graph->pile = remove_command(graph->pile);
        }
    }
    return game;
}

tile_t **refresh_map(game_t *game, tile_t **tile)
{
    int element[7];
    int ratio, randi, rando;

    if (game->map->Y > game->map->X) ratio = game->map->Y;
    else ratio = game->map->X;
    element[0] = game->clientNB * game->teamnb * ratio;
    element[1] = game->clientNB * game->teamnb * ratio;
    element[2] = game->clientNB * game->teamnb * ratio;
    element[3] = game->clientNB * game->teamnb * ratio;
    element[4] = game->clientNB * game->teamnb * ratio;
    element[5] = game->clientNB * game->teamnb * ratio;
    element[6] = game->clientNB * game->teamnb * ratio;
    for (int i = 0; i < 7; i++) {
        for (; element[i] > 0; element[i]--) {
            rando = my_rand() % game->map->Y;
            randi = my_rand() % game->map->X;
            tile[rando][randi].resource[i]++;
        }
    }
    return tile;
}

game_t *time_gestion(game_t *game)
{
    //static int compteur = 0;

    if (game->tv.tv_usec == 0 && game->tv.tv_sec == 0 && !game->is_end) {
        game->tv.tv_usec = 1000000 / game->freq;
        game->tv.tv_sec = 0;
        //compteur++;
        for (player_t *mem = game->player; mem != NULL; mem = mem->next) {
            if (mem->game->id_inc != NULL
            && mem->game->funct != &incantation_end);
            else mem->game->cooldown--;
            if (mem->game->is_egg != IS)
                mem->game->cpt--;
        }
    }
    /*if (compteur == 1260) {
        compteur = 0;
        game->map->tiles = refresh_map(game, game->map->tiles);
        for (graphics_t *t = game->graph; t != NULL; t = t->next)
            t->pile = add_command(t->pile, "mct");
    }*/
    return game;
}