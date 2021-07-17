/*
** EPITECH PROJECT, 2020
** Created by theo on 11/06/2020.
** File description:
** serv_tools.c
*/

#include "rfc_ia.h"

char *new_uuid(void)
{
    uuid_t test;
    char *uuid = my_malloc(37);

    uuid_generate_random(test);
    uuid_unparse(test, uuid);
    uuid[36] = '\0';
    return uuid;
}

int my_rand(void)
{
    static int first = 0;

    if (first == 0) {
        srand(time(NULL));
        first = 1;
    }
    return (rand());
}

char *my_charcat(char *res, char ret)
{
    int l = my_strlen(res) + 1;

    if (res == NULL)
        res = my_malloc(l + 1);
    else
        res = realloc(res, l + 1);
    res[l - 1] = ret;
    res[l] = '\0';
    return (res);
}

int my_strcmp(char *str, char *dest)
{
    int size1 = my_strlen(str);
    int size2 = my_strlen(dest);

    if (size1 != size2)
        return -1;
    if (str == NULL || dest == NULL)
        return -1;
    for (int i = 0; i < size1; i++) {
        if (str[i] != dest[i])
            return -1;
    }
    return 0;
}