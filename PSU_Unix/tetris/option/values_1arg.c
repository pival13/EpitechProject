/*
** EPITECH PROJECT, 2019
** values_1arg.c
** File description:
** values_1arg
*/

#include "my.h"

int options_1arg_map_size_values(char *value1, char *value2, char *value)
{
    int pos = 0;

    for (int i = 0, j = 0; value[i] != 0; i++) {
        (pos == 0) ? (value1[i] = value[i]) : (value2[j] = value[i], j++);
        (value[i] == ',') ? (pos = 1) : (0);
    }
    value1[my_strlen(value1) - 1] = 0;
    if (value2 == 0)
        return (84);
    return (0);
}

int options_1arg_level_map_size(tetris_t *w, char *opt, char *value)
{
    char *value1 = create_string(20);
    char *value2 = create_string(20);
    int ret = 0;

    if (my_strcmp(opt, "--level=") == 0) {
        w->lvl = my_getnbr(value);
        ret = 1;
    }
    if (my_strcmp(opt, "--map-size=") == 0) {
        if (options_1arg_map_size_values(value1, value2, value) != 84) {
            w->size[0] = my_getnbr(value1);
            w->size[1] = my_getnbr(value2);
            ret = 1;
        }
    }
    free(value1);
    free(value2);
    return (ret);
}

int options_1arg_1char(tetris_t *w, char *opt, char *value)
{
    int val = value[0];

    (my_strcmp(opt, "--key-left=") == 0) ? (w->left = val) : (0);
    (my_strcmp(opt, "--key-right=") == 0) ? (w->right = val) : (0);
    (my_strcmp(opt, "--key-turn=") == 0) ? (w->rotate = val) : (0);
    (my_strcmp(opt, "--key-drop=") == 0) ? (w->down = val) : (0);
    (my_strcmp(opt, "--key-quit=") == 0) ? (w->exit = val) : (0);
    (my_strcmp(opt, "--key-pause=") == 0) ? (w->pause = val) : (0);
    return (0);
}

int options_1arg_2char(tetris_t *w, char *opt, char *value)
{
    int val = 0;

    (my_strcmp(value, "\n") == 0) ? (val = '\n') : (0);
    (my_strcmp(value, "\t") == 0) ? (val = '\t') : (0);
    if (val == 0)
        return (84);
    (my_strcmp(opt, "--key-left=") == 0) ? (w->left = val) : (0);
    (my_strcmp(opt, "--key-right=") == 0) ? (w->right = val) : (0);
    (my_strcmp(opt, "--key-turn=") == 0) ? (w->rotate = val) : (0);
    (my_strcmp(opt, "--key-drop=") == 0) ? (w->down = val) : (0);
    (my_strcmp(opt, "--key-quit=") == 0) ? (w->exit = val) : (0);
    (my_strcmp(opt, "--key-pause=") == 0) ? (w->pause = val) : (0);
    return (0);
}

int options_1arg_set_values(tetris_t *w, char *opt, char *value)
{
    int res = 0;

    res = options_1arg_level_map_size(w, opt, value);
    if (res == 0 && my_strlen(value) > 2) {
        return (84);
    }
    if (res == 1)
        return (0);
    if (my_strlen(value) == 1) {
        return (options_1arg_1char(w, opt, value));
    } else if (my_strlen(value) == 2) {
        return (options_1arg_2char(w, opt, value));
    } else {
        return (84);
    }
    return (0);
}
