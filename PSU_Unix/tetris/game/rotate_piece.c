/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** main loop of tetris
*/

#include "tetris.h"

char **copy_tab(char **tab, int *pos)
{
    char **copy = malloc(sizeof(char *) * pos[3]);

    for (int i = 0; i != pos[3]; i++) {
        copy[i] = malloc(sizeof(char) * pos[2]);
        for (int j = 0; j != pos[2]; j++) {
            copy[i][j] = tab[pos[1]+i][pos[0]+j];
            tab[pos[1]+i][pos[0]+j] = '0';
        }
    }
    return (copy);
}

void get_position(tetris_t *w, int *pos)
{
    for (int i = 0; i != w->size[0]; i++)
        for (int j = 0; j != w->size[1]; j++) {
            if (w->map[i][j] > '0' && w->map[i][j] <= '9' && pos[0] > j)
                pos[0] = j;
            if (w->map[i][j] > '0' && w->map[i][j] <= '9' && pos[1] > i)
                pos[1] = i;
            if (w->map[i][j] > '0' && w->map[i][j] <= '9' && pos[2] < j)
                pos[2] = j;
            if (w->map[i][j] > '0' && w->map[i][j] <= '9' && pos[3] < i)
                pos[3] = i;
        }
    pos[2] = pos[2] - pos[0] + 1;
    pos[3] = pos[3] - pos[1] + 1;
}

void rotate_piece(tetris_t *w)
{
    int pos[4] = {w->size[1], w->size[0], 1, 1};
    char **copy;

    get_position(w, pos);
    if (pos[1]+pos[2] > w->size[0] || pos[0]+pos[3] > w->size[1])
        return;
    for (int i = 0; i != pos[2]; i++)
        for (int j = 0; j != pos[3]; j++)
            if (w->map[pos[1]+i][pos[0]+j] > 'a')
                return;
    copy = copy_tab(w->map, pos);
    for (int i = 0; i != pos[2]; i++)
        for (int j = 0; j != pos[3]; j++)
            w->map[pos[1]+i][pos[0]+j] = copy[pos[3]-1-j][i];
    for (int i = 0; i != pos[3]; i++)
        free(copy[i]);
    free(copy);
}
