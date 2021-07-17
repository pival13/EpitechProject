/*
** EPITECH PROJECT, 2020
** Created by theo on 11/06/2020.
** File description:
** graph_other.c
*/

#include "rfc.h"

char *death(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(64);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = '\0';
    return rfc;
}

char *resource_collecting(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(64);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}

char *resource_dropping(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(64);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}

char *end_incantation(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(my_strlen(cmd) + 1);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}

char *start_incantation(char *cmd, __attribute__((unused))game_t *game)
{
    char *rfc = my_malloc(my_strlen(cmd) + 1);
    int i = 0;

    for (; cmd[i] != '\0'; i++)
        rfc[i] = cmd[i];
    rfc[i] = 0;
    return rfc;
}