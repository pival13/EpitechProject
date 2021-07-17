/*
** EPITECH PROJECT, 2020
** Created by theo on 11/06/2020.
** File description:
** graphs_egg.c
*/

#include "rfc.h"

char *egg_laying_other(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(my_strlen(cmd) + 1);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}

char *egg_laying(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(my_strlen(cmd) + 1);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}

char *graph_egg_hatching(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(my_strlen(cmd) + 1);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}

char *connect_egg(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(my_strlen(cmd) + 1);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}