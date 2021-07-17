/*
** EPITECH PROJECT, 2019
** errors_tetris.c
** File description:
** errors management tetris
*/

#include "my.h"
#include <sys/ioctl.h>

int errors_tetris2(tetris_t *w)
{
    int error = 0;
    struct winsize win;

    ioctl(0, TIOCGWINSZ, &win);
    (w->lvl <= 0) ? (error = 85) : (0);
    if (error == 84)
        my_putstr_error("Invalid map size.\n");
    if (error == 85) {
        my_putstr_error("Invalid level value.\n");
        error = 84;
    }
    return (error);
}

int is_key_special(int key)
{
    int ret = 0;

    (key == KEY_UP) ? (ret = 1) : (0);
    (key == KEY_DOWN) ? (ret = 1) : (0);
    (key == KEY_RIGHT) ? (ret = 1) : (0);
    (key == KEY_LEFT) ? (ret = 1) : (0);
    (key == '\t') ? (ret = 1) : (0);
    (key == '\n') ? (ret = 1) : (0);
    return (ret);
}

int put_error_msg(int error)
{
    if (error == 84) {
        my_putstr_error("Invalid key.\n");
    }
    if (error == 85) {
        my_putstr_error("Some commands have the same key.\n");
        error = 84;
    }
    return (error);
}

int errors_tetris(tetris_t *w)
{
    int error = 0;
    int keys[6];

    keys[0] = w->left;
    keys[1] = w->right;
    keys[2] = w->down;
    keys[3] = w->rotate;
    keys[4] = w->exit;
    keys[5] = w->pause;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            (i != j && keys[i] == keys[j]) ? (error = 85) : (0);
            ((keys[j] < 32 || keys[j] > 127) &&
            is_key_special(keys[j]) == 0) ? (error = 84) : (0);
        }
    error = put_error_msg(error);
    (errors_tetris2(w) == 84) ? (error = 84) : (0);
    return (error);
}
