/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** my_strcat
*/

#include "server.h"

/**
* @brief Merge to string into one.
*
* @param str Destination string.
* @param str2 Const string to add to the first one.
*/
void my_strcat(char **str, const char *str2)
{
    size_t len = 0;
    char *tmp = NULL;
    int index = 0;

    if (str2 == NULL)
        return;
    ((*str) == NULL) ? (len = strlen(str2)) : \
(len = strlen(*str) + strlen(str2));
    tmp = malloc(sizeof(char) * (len + 1));
    memset(tmp, 0, len + 1);
    if (*str != NULL)
        for (int a = 0; (*str)[a] != '\0'; ++a, ++index)
            tmp[index] = (*str)[a];
    for (int a = 0; str2[a] != '\0'; ++a, ++index)
        tmp [index] = str2[a];
    free(*str);
    (*str) = strdup(tmp);
    free(tmp);
}
