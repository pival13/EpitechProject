/*
** EPITECH PROJECT, 2019
** options_tetris.c
** File description:
** options for tetris
*/

#include "my.h"

char *traduce_options(char *buffer, char *str1)
{
    int res = 0;

    if (str1[0] == '-') {
        if (str1[1] == 'L' || str1[1] == 'l' || str1[1] == 'r'
            || str1[1] == 't')
            res = 1;
        if (str1[1] == 'd' || str1[1] == 'q' || str1[1] == 'p')
            res = 1;
    }
    if (res == 0)
        return (NULL);
    (my_strcmp(str1, "-L") == 0) ? (buffer = my_strcpy("--level=")) : (0);
    (my_strcmp(str1, "-l") == 0) ? (buffer = my_strcpy("--key-left=")) : (0);
    (my_strcmp(str1, "-r") == 0) ? (buffer = my_strcpy("--key-right=")) : (0);
    (my_strcmp(str1, "-t") == 0) ? (buffer = my_strcpy("--key-turn=")) : (0);
    (my_strcmp(str1, "-d") == 0) ? (buffer = my_strcpy("--key-drop=")) : (0);
    (my_strcmp(str1, "-q") == 0) ? (buffer = my_strcpy("--key-quit=")) : (0);
    (my_strcmp(str1, "-p") == 0) ? (buffer = my_strcpy("--key-pause=")) : (0);
    return (buffer);
}

int options_2arg(tetris_t *w, char *str1, char *str2)
{
    char *buffer = NULL;
    int ret = 84;

    buffer = traduce_options(buffer, str1);
    if (buffer != NULL)
        ret = options_1arg_set_values(w, buffer, str2);
    return (ret);
}

int options_1arg(tetris_t *w, char *str)
{
    char *buffer = create_string(254);
    char *value = create_string(254);
    int ret = 0;
    int good = 0;

    for (int i = 0, j = 0; str[i] != 0; i++) {
        (good == 1) ? (value[j] = str[i], j++) : (buffer[i] = str[i]);
        (str[i] == '=') ? (good = 1) : (0);
    }
    if (good == 1)
        ret = options_1arg_set_values(w, buffer, value);
    free(buffer);
    free(value);
    return (ret);
}

int options_tetris_keys(tetris_t *w, char *str1, char *str2)
{
    int ret = 0;

    if (my_strlen(str1) < 2 || is_nbr(str1) == 1)
        return (0);
    if (my_strcmp(str1, "-w") == 0 || my_strcmp(str1, "--without-next") == 0) {
        w->next = 0;
        return (0);
    }
    if (my_strcmp(str1, "--help") == 0 || my_strcmp(str1, "-h") == 0) {
        return (0);
    }
    if (str1[0] == '-' && str1[1] == '-') {
        ret = options_1arg(w, str1);
    } else if (str2 != NULL)
        ret = options_2arg(w, str1, str2);
    else
        ret = 84;
    return (ret);
}

int options_tetris(tetris_t *w, char **arg, int n)
{
    int debug = 0;
    int ret = 0;

    for (int i = 1; i < n; i++) {
        if (my_strcmp(arg[i], "-D") == 0 || my_strcmp(arg[i], "--debug") == 0) {
            debug = 1;
            ret = 0;
        } else if (i + 1 < n)
            ret = options_tetris_keys(w, arg[i], arg[i+1]);
        else
            ret = options_tetris_keys(w, arg[i], NULL);
        if (ret == 84) {
            my_putstr_error("Invalid option.\n");
            return (84);
        }
    }
    return (debug);
}
