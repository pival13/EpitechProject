/*
** EPITECH PROJECT, 2019
** is_something_ci.c
** File description:
** is_something for check_input
*/

#include "my.h"

int print_bug(char **arr, int id)
{
    if (id < 0)
        return (id);
    for (int i = 0; i < id; i++) {
        my_printf("%s\n", arr[i]);
    }
    return (id);
}

int is_room_ci(char *arr)
{
    int i = 0;
    if (arr == NULL)return (0);
    if (arr[0] == '#')return (0);
    if (is_tunnel_ci(arr) == -1)
        return (-3);
    for (; is_alphanum(arr[i]); i++);
    if (arr[i] == ' ') i++;
    else return (-2);
    for (; arr[i] <= '9' && arr[i] >= '0'; i++);
    if (arr[i] == ' ') i++;
    else return (-2);
    for (; arr[i] <= '9' && arr[i] >= '0'; i++);
    if (arr[i] == ' ') i++;
    for (; arr[i] != 0; i++) {
        if (arr[i] == '#')
            return (1);
        if (arr[i] > 0 && arr[i] != '\n' && arr[i] != ' ')
            return (-2);
    }
    return (1);
}

int is_tunnel_ci(char *arr)
{
    int i = 0;

    if (arr == NULL)
    return (0);
    for (; is_alphanum(arr[i]); i++);
    if (arr[i] == '-')
        i++;
    else
        return (-2);
    for (; is_alphanum(arr[i]); i++);
    return (-1);
}
