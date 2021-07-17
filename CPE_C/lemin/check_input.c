/*
** EPITECH PROJECT, 2019
** check_input
** File description:
** checkinput
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "my.h"

int verify_ants(char *array)
{
    int i = 0;

    for (i; array[i] != '\0' && array[i] != '#'; i++)
        if (array[i] > 57 || array[i] < 48)
            return 1;
    return 0;
}

int verify(char *array_i, char *comp)
{
    int i = 0;
    int j = 0;

    for (; array_i[i] != ' ' && array_i[i] != '\0' && array_i[i] != '#'; i++);
    for (; comp[j] != '\0'; j++);
    if (j != i)
        return (1);
    for (int i = 0; comp[i] != '\0'; i++)
        if (array_i[i] != comp[i])
            return (1);
    if (array_i[i] != '\n' || array_i[i] != '\0' || array_i[i] != ' ' || \
        array_i[i] != '\t')
        return (1);
    return (0);
}

int check2(char **array, int i, int save, int save2)
{
    if (save == 0 || save2 == 0)
        return (-2);
    for (; array[i] != NULL; i++)
        if (is_tunnel_ci(array[i]) == -1)
            return (-1);
        else if (is_tunnel_ci(array[i]) == -2)
            return (i);
    return (-2);
}

int check(char **array)
{
    int save = 0;
    int save2 = 0;
    int i = 0;
    if (array == NULL)return (1);
    if (is_int(array[0]) == 1 || my_getnbr(array[0]) < 1)return (1);
    for (i = 1; array[i] != NULL; i++) {
        if (is_room_ci(array[i]) == -2)return (i);
        if (is_room_ci(array[i]) == -3)break;
    }
    for (int k = 0; array[k] != NULL; k++) {
        if (array[k][0] == '#' && (my_strcmp(array[k], "##start") != 0 && \
            my_strcmp(array[k], "##end") != 0)) {
            for (int j = k; array[j] != NULL; j++) array[j] = array[j+1];
            k--;
        }
        if (my_strcmp(array[k], "##start") == 0 && is_room_ci(array[k + 1]))
            save = k;
        else if (my_strcmp(array[k], "##end") == 0 && is_room_ci(array[k + 1]))
            save2 = k;
    }
    return (check2(array, i, save, save2));
}

char **check_input(void)
{
    int i = 0;
    char **doublearray = NULL;
    char **tab = NULL;
    char *buffer = NULL;
    char *all_buffer = NULL;

    while (1) {
        buffer = get_next_line(0);
        if (buffer == NULL || buffer[0] == '\0') break;
        all_buffer = copy(all_buffer, buffer);
    }
    if (all_buffer == NULL)
        return (NULL);
    doublearray = get_words(all_buffer);
    if (print_bug(doublearray, check(doublearray)) != -1)
        return (NULL);
    for (i = 0; doublearray[i] != NULL; ++i);
    tab = malloc(sizeof(char *) * (i + 1));
    tab = read_all(tab, all_buffer, doublearray);
    return (tab);
}
