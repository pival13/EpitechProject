/*
** EPITECH PROJECT, 2020
** Created by theo on 20/06/2020.
** File description:
** look_tools.c
*/

#include "my.h"

char *look_the_north(player_t *client, game_t *game)
{
    char *response = NULL;

    for (int i = 0; i <= client->game->level; i++) {
        for (int X = (client->game->posX - i), Y = (
            client->game->posY - i);
            X <= (client->game->posX + i); X = (X + 1)) {
            response = my_strcat(response,
                check_case(((X < 0) ? X + game->map->X : X) % game->map->X,
                    ((Y < 0) ? Y + game->map->Y : Y) % game->map->Y, game));
            if (X == (client->game->posX + i) % game->map->X &&
                i == client->game->level + 1);
            else
                response = my_charcat(response, ',');
        }
    }
    return response;
}

char *look_the_east(player_t *client, game_t *game)
{
    char *response = NULL;

    for (int i = 0; i <= client->game->level; i++) {
        for (int Y = client->game->posY - i, X = (
            client->game->posX + i);
            Y <= (client->game->posY + i); Y = (Y + 1)) {
            response = my_strcat(response,
                check_case(((X < 0) ? X + game->map->X : X) % game->map->X,
                    ((Y < 0) ? Y + game->map->Y : Y) % game->map->Y, game));
            response = my_charcat(response, ',');
        }
    }
    return response;
}

char *look_the_south(player_t *client, game_t *game)
{
    char *response = NULL;

    for (int i = 0; i <= client->game->level; i++) {
        for (int X = (client->game->posX + i), Y = (
            client->game->posY + i);
            X >= (client->game->posX - i); X = (X - 1)) {
            response = my_strcat(response,
                check_case(((X < 0) ? X + game->map->X : X) % game->map->X,
                    ((Y < 0) ? Y + game->map->Y : Y) % game->map->Y, game));
            response = my_charcat(response, ',');
        }
    }
    return response;
}

char *look_the_west(player_t *client, game_t *game)
{
    char *response = NULL;

    for (int i = 0; i <= client->game->level; i++) {
        for (int Y = (client->game->posY + i), X = (
            client->game->posX - i);
            Y >= (client->game->posY - i); Y = (Y - 1)) {
            response = my_strcat(response,
                check_case(((X < 0) ? X + game->map->X : X) % game->map->X,
                    ((Y < 0) ? Y + game->map->Y : Y) % game->map->Y, game));
            response = my_charcat(response, ',');
        }
    }
    return response;
}