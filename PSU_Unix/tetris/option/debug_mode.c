/*
** EPITECH PROJECT, 2019
** debug_mode.c
** File description:
** debug mode
*/

#include "my.h"

void debug_mode_tetriminos_pieces(tetris_t *w, int nb)
{
    for (int i = 0; w->piece[nb].piece[i] != NULL; i++)
        my_printf("%s\n", w->piece[nb].piece[i]);
}

void debug_mode_tetriminos(tetris_t *w)
{
    int piece = 0;

    for (; w->piece[piece].name != NULL; piece++);
    my_printf("Tetriminos :  %d\n", piece);
    for (int nb = 0; w->piece[nb].name != NULL; nb++) {
        my_printf("Tetriminos :  Name %s :  ", w->piece[nb].name);
        if (w->piece[nb].size[0] == 0 || w->piece[nb].size[1] == 0
            || w->piece[nb].color == 0)
            my_printf("Error\n");
        else {
            my_printf("Size %d*%d :  Color %d :\n",
            w->piece[nb].size[0], w->piece[nb].size[1], w->piece[nb].color);
            debug_mode_tetriminos_pieces(w, nb);
        }
    }
}

char *debug_mode_char(int value, char *c)
{
    for (int i = 0; i < 255; c[i] = 0, i++);
    c[0] = value;
    (value == ' ') ? (c = "(space)") : (0);
    (value == KEY_LEFT) ? (c = "^EOD") : (0);
    (value == KEY_RIGHT) ? (c = "^EOC") : (0);
    (value == KEY_DOWN) ? (c = "^EOB") : (0);
    (value == KEY_UP) ? (c = "^EOA") : (0);
    (value == '\t') ? (c = "(horizontal tab)") : (0);
    (value == '\n') ? (c = "(new line)") : (0);
    (value == 27) ? (c = "(ESC)") : (0);
    return (c);
}

void debug_mode_commands(tetris_t *w)
{
    char *str_use = malloc(sizeof(char) * 255);

    my_printf("Key Left :  %s\n", debug_mode_char(w->left, str_use));
    my_printf("Key Right :  %s\n", debug_mode_char(w->right, str_use));
    my_printf("Key Turn :  %s\n", debug_mode_char(w->rotate, str_use));
    my_printf("Key Drop :  %s\n", debug_mode_char(w->down, str_use));
    my_printf("Key Quit :  %s\n", debug_mode_char(w->exit, str_use));
    my_printf("Key Pause :  %s\n", debug_mode_char(w->pause, str_use));
    if (w->next)
        my_printf("Next :  Yes\n");
    else
        my_printf("Next :  No\n");
    my_printf("Level :  %d\n", w->lvl);
    my_printf("Size :  %d*%d\n", w->size[0], w->size[1]);
    free(str_use);
}

int debug_mode(tetris_t *w)
{
    my_printf("*** DEBUG MODE ***\n");
    debug_mode_commands(w);
    debug_mode_tetriminos(w);
    my_printf("Press any key to start Tetris\n");
    if (press_any_key() == 84)
        return (84);
    return (0);
}
