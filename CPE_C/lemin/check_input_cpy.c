/*
** EPITECH PROJECT, 2019
** check_input_cpy.c
** File description:
** rewriting funcs
*/

#include "my.h"

int my_strlength(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return (i);
}

char *delete_end(char *str)
{
    int d = 0;
    int i = my_strlength(str) - 2;
    char *strcpi = malloc(sizeof(char) * my_strlength(str) + 3);

    if (strcpi == NULL)
        return (NULL);
    while (str[i] == ' ' || str[i] == '\t')
        i--;
    while (d != i + 1) {
        strcpi[d] = str[d];
        d++;
    }
    strcpi[d] = '\n';
    strcpi[d + 1] = '\0';
    return (strcpi);
}

char *copy(char *all_buffer, char *buffer)
{
    char *save = my_strcpy(all_buffer);
    int i = 0;
    int j = 0;

    if (save != NULL)
        for (i = 0; save[i] != '\0'; i++);
    for (; buffer[j] != '\0'; j++);
    if (all_buffer != NULL)
        free(all_buffer);
    all_buffer = malloc(sizeof(char) * (i + j + 2));
    if (all_buffer == NULL)
        return (NULL);
    i = 0;
    if (save != NULL)
        for (; save[i] != '\0'; all_buffer[i] = save[i], i++);
    for (j = 0; buffer[j] != '\0'; j++, i++)all_buffer[i] = buffer[j];
    all_buffer[i] = '\n';
    all_buffer[i + 1] = '\0';
    return all_buffer;
}

char *copy_until_n(int i, char **doublearray)
{
    int j = 0;
    char *save = NULL;

    for (i = 0; doublearray[i] != NULL; ++i)
        if (verify_ants(doublearray[i]) == 0)break;
    for (; doublearray[i][j] != '\0' && doublearray[i][j] != '#' \
        && doublearray[i][j] != '\n' && doublearray[i][j] != ' '; j++);
    save = malloc(sizeof(char) * (j + 1));
    for (j = 0; doublearray[i][j] != '\0' && doublearray[i][j] != '#' \
        && doublearray[i][j] != '\n' && doublearray[i][j] != ' '; j++)
        save[j] = doublearray[i][j];
    save[j] = '\0';
    return save;
}

char *cp_until_diez(char *str)
{
    int i = 0;
    char *save = NULL;
    int space = 0;

    for (i = 0; str[i] != '#' && str[i] != '\0' && str[i] != '\n'; ++i) {
    if (str[i] == ' ')
            space++;
        if (space == 3)
            break;
    }
    save = malloc(sizeof(char) * (i + 1));
    if (save == NULL)
        return (NULL);
    for (int j = 0; j != i; ++j)
        save[j] = str[j];
    save[i] = '\0';
    return (save);
}
