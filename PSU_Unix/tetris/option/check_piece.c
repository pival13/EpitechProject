/*
** EPITECH PROJECT, 2019
** create_tetrimino
** File description:
** create the tetrimino
*/

#include "my.h"

void check_each_line(tetrimino_t piece, int i, int *ok)
{
    int max = 1;

    if (piece.piece[i] == NULL)
        *ok = 0;
    for (int j = 0; *ok && j != piece.size[0]; j++) {
        if (piece.piece[i][j] == '\0') {
            *ok -= 1;
            j = piece.size[0]-1;
            max = 0;
        } else if (j == piece.size[0]-1 && piece.piece[i][j] != '*')
            *ok -= 1;
        if (piece.piece[i][j] != '*' && piece.piece[i][j] != ' ' && piece.\
piece[i][j] != '\0')
            *ok = 0;
    }
    for (int j = piece.size[0]; *ok && max && piece.piece[i][j] != '\0'; j++)
        if (piece.piece[i][j] != ' ')
            *ok = 0;
}

int check_piece(tetrimino_t piece)
{
    int ok = piece.size[1];

    for (int i = 0; ok && i != piece.size[1]; i++)
        check_each_line(piece, i, &ok);
    for (int i = piece.size[1]; ok && piece.piece[i] != NULL; i++)
        for (int j = 0; piece.piece[i][j] != '\0'; j++)
            if (piece.piece[i][j] != ' ')
                ok = 0;
    return (ok);
}

