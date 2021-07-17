/*
** EPITECH PROJECT, 2019
** check_input_room.c
** File description:
** check rooms input
*/

#include "my.h"

char *first_room(char **darray)
{
    int i = 0;
    int space = 0;

    for (; darray[i] != NULL; i++) {
        if (my_strcmp(darray[i], "##start") == 0)
            return (cp_until_diez(darray[i + 1]));
    }
    return (NULL);
}

char *last_room(char **darray)
{
    int i = 0;

    for (; darray[i] != NULL; i++)
        if (my_strcmp(darray[i], "##end") == 0)
            return (cp_until_diez(darray[i + 1]));
    return (NULL);
}

char **tab_room(char **tab, int *i, char **arr)
{
    for (int j = 0; arr[j] != NULL; j++) {
        if (is_room_ci(arr[j]) == 1) {
            while (arr[j][0] == '#')
        j++;
            if (my_strcmp(arr[j - 1], "##end") != 0 && \
            my_strcmp(arr[j - 1], "##start") != 0) {
                tab[*i] = cp_until_diez(arr[j]);
                *i += 1;
            }
        }
    }
    return (tab);
}

char **tab_tunnel(char **tab, int *i, char **arr)
{
    for (int j = 0; arr[j] != NULL; j++) {
        if (is_tunnel_ci(arr[j]) == -1) {
            while (arr[j][0] == '#')
                j++;
            if (my_strcmp(arr[j - 1], "##end") != 0 && \
            my_strcmp(arr[j - 1], "##start") != 0) {
            tab[*i] = cp_until_diez(arr[j]);
                *i += 1;
            }
        }
    }
    return (tab);
}

char **read_all(char **tab, char *all_buffer, char **arr)
{
    int i = 0;
    int save = 0;
    int save2 = 0;

    tab[0] = copy_until_n(0, arr);
    tab[1] = first_room(arr);
    tab[2] = last_room(arr);
    i = 3;
    tab = tab_room(tab, &i, arr);
    tab = tab_tunnel(tab, &i, arr);
    tab[i] = NULL;
    for (i = 3; tab[i] != NULL; i++) {
        if (my_strcmp_ci(tab[i], tab[1]) == 0 || my_strcmp_ci_end \
            (tab[i], tab[1]) == 0 )save++;
        if (my_strcmp_ci_end(tab[i], tab[2]) == 0 || my_strcmp_ci\
            (tab[i], tab[2]) == 0)save2++;
    }
    if (save == 0 || save2 == 0)return NULL;
    return (tab);
}
