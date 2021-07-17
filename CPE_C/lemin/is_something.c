/*
** EPITECH PROJECT, 2019
** is something
** File description:
** is something
*/

#include <stddef.h>

int is_int(const char *str)
{
    for (int i = 0; str[i] != '#' && str[i] != '\0'
    && str[i] != ' ' && str[i] != '\t' && str[i] != '\n'; ++i)
        if (str[i] > 57 || str[i] < 48)return 1;
    return 0;
}

int is_alphanum(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))
        return (1);
    else if (c >= 'A' && c <= 'Z')
        return (1);
    else
        return (0);
}

int is_room(char *arr)
{
    int i = 0;
    if (arr == NULL)
        return (0);
    if (arr[0] == '#')
        return (0);
    for (; is_alphanum(arr[i]); i++);
    if (arr[i] == ' ') i++;
    else return (0);
    for (; arr[i] <= '9' && arr[i] >= '0'; i++);
    if (arr[i] == ' ') i++;
    else return (0);
    for (; arr[i] <= '9' && arr[i] >= '0'; i++);
    return 1;
}

int is_tunnel(char *arr)
{
    int i = 0;

    if (arr == NULL) return (0);
    for (; is_alphanum(arr[i]); i++);
    if (arr[i] == '-') i++;
    else return (0);
    for (; is_alphanum(arr[i]); i++);
    return 1;
}
