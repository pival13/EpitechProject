/*
** EPITECH PROJECT, 2019
** create_tetrimino
** File description:
** create the tetrimino
*/

#include "my.h"

void get_name(char *path, tetrimino_t *tetris, int nb)
{
    int i = 0;
    int j = 0;

    for (; path[i] != '\0'; i++) {
        if (path[i] == '/')
            j = i + 1;
        if (path[i] == '.' && !my_strcmp(&path[i], ".tetrimino")) {
            tetris[nb].name = my_strncpy(&path[j], i-j);
        }
    }
}

void check_tetrimino(char *path, tetrimino_t *tetris)
{
    char *file = read_fd_stat(path);
    int i = 0;
    int nb = 0;

    for (; tetris[nb].name != NULL; nb++);
    tetris[nb+1].name = NULL;
    get_name(path, tetris, nb);
    for (int j = 0; file != NULL && j != 2; j++) {
        tetris[nb].size[j] = my_getnbr(&file[i]);
        if (tetris[nb].size[0] == 0)
            break;
        for (; file[i] > '0' && file[i] < '9'; i++);
        for (; file[i] == ' ' || file[i] == '\t'; i++);
    }
    tetris[nb].color = my_getnbr(&file[i]);
    tetris[nb].piece = get_words(&file[i+1]);
    if (!check_piece(tetris[nb]))
        tetris[nb].color = 0;
}

void order_tetrimino(tetrimino_t **tetris)
{
    tetrimino_t mem;

    for (int i = 1; tetris[0][i].name != NULL;) {
        if (i < 1)
            i = 1;
        if (my_strcmp(tetris[0][i].name, tetris[0][i-1].name) < 0) {
            mem = tetris[0][i-1];
            tetris[0][i-1] = tetris[0][i];
            tetris[0][i] = mem;
            i--;
        } else
            i++;
    }
}

int nb_piece(void)
{
    DIR *dir;
    struct dirent *cont;
    int nb = 0;

    dir = opendir("./tetriminos");
    if (dir == NULL)
        return (0);
    cont = readdir(dir);
    while (cont != NULL) {
        if (my_strcmp(cont->d_name, ".") && my_strcmp(cont->d_name, ".."))
            nb++;
        cont = readdir(dir);
    }
    return (nb);
}

tetrimino_t *create_tetrimino(tetrimino_t *w)
{
    DIR *dir;
    struct dirent *cont;
    int piece = nb_piece();

    w = malloc(sizeof(tetrimino_t) * (piece+1));
    if (piece == 0 || w == NULL)
        return (NULL);
    w[0].name = NULL;
    dir = opendir("./tetriminos");
    if (dir == NULL)
        return (NULL);
    cont = readdir(dir);
    while (cont != NULL) {
        if (my_strcmp(cont->d_name, ".") && my_strcmp(cont->d_name, ".."))
            check_tetrimino(my_merge_3("./tetriminos", "/", cont->d_name), w);
        cont = readdir(dir);
    }
    order_tetrimino(&w);
    return (w);
}
