/*
** EPITECH PROJECT, 2019
** add .core
** File description:
** overwrite .s
*/

#include "my.h"

char *without_path(char *str)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char *save = NULL;

    for (; str[i] != '\0'; i++);
    j = i;
    for (; i >= 0 && str[i] != '/'; i--);
    save = malloc(sizeof(char) * (j - i + 1));
    if (save == NULL)
        return (NULL);
    i++;
    for (; str[i] != '\0'; i++, k++)
        save[k] = str[i];
    save[k] = '\0';
    return save;
}

char *good_file(char *str)
{
    int lenght = my_strlen(str);
    char *save = NULL;
    char *core = ".cor\0";
    int i = 0;

    if (str[lenght-1] == 's' && str[lenght-2] == '.') {
        save = malloc(sizeof(char) * (lenght+3));
        if (save == NULL)
            return (NULL);
        lenght -= 2;
    } else {
        save = malloc(sizeof(char) * (lenght+6));
        if (save == NULL)
            return (NULL);
    }
    for (i = 0; i != lenght; i++)
        save[i] = str[i];
    for (int j = 0; core[j] != '\0'; j++, i++)
        save[i] = core[j];
    save[i] = '\0';
    return save;
}

int return_fd(char *str)
{
    int fd = 0;
    char *save = NULL;
    char *path = NULL;

    save = good_file(str);
    path = without_path(save);
    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    free(save);
    free(path);
    if (fd <= 0)
        return -1;
    return fd;
}

char **delete_bad_character(char **tab, int i, int j)
{
    for (j = 0; tab[i][j]; ++j) {
        if (tab[i][j] == '\t')
            tab[i][j] = ' ';
        if (tab[i][j] == COMMENT_CHAR)
            tab[i][j] = '\0';
    }
    return (tab);
}

char **space_gestion(char **tab, int i, int j)
{
    for (j = 1; tab[i][0] && tab[i][j]; j++)
        if (tab[i][j-1] == ' ' && tab[i][j] == ' ') {
            delete_chara(tab[i], j);
            j--;
        }
    for (j = 0; tab[i][j]; j++)
        if (tab[i][j] == LABEL_CHAR && tab[i][j+1] == ' ') {
            delete_chara(tab[i], j+1);
            j--;
        }
    return (tab);
}
