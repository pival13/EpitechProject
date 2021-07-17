/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of tetris
*/

#include "my.h"

tetris_t *create_tetris(void)
{
    tetris_t *w = malloc(sizeof(tetris_t));

    w->piece = create_tetrimino(w->piece);
    w->left = KEY_LEFT;
    w->right = KEY_RIGHT;
    w->down = KEY_DOWN;
    w->rotate = KEY_UP;
    w->pause = ' ';
    w->exit = 'q';
    w->next = 1;
    w->size[0] = 20;
    w->size[1] = 10;
    w->lvl = 1;
    w->speed = 1;
    if (w->piece == NULL) return (NULL);
    return (w);
}

int destroy_tetris(tetris_t *w)
{
    free(w);
    return (0);
}

int main(int n, char **arg, char **env)
{
    tetris_t *w;
    int debug = 0;

    if (help_option(arg, n) == 1)
        return (0);
    if (env == NULL || term_check(env) == 84)
        return (84);
    w = create_tetris();
    if (w == NULL)
        return (84);
    debug = options_tetris(w, arg, n);
    (debug == 84 || errors_tetris(w) == 84) ? (destroy_tetris(w)) : (0);
    if (debug == 84 || errors_tetris(w) == 84)
        return (84);
    (debug == 1) ? (debug = debug_mode(w)) : (0);
    (term_check(env) == 83 || debug == 84) ? (destroy_tetris(w)) : (0);
    if (term_check(env) == 83 || debug == 84)
        return (0);
    tetris(w);
    return (destroy_tetris(w));
}
