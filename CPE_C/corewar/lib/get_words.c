/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of sort_words
*/

#include <stdlib.h>
#include <unistd.h>
#include "op.h"

static int find_nb_words(char *str)
{
    int nb_words = 0;
    int new_word = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (new_word == 1 && str[i] != SEPARATOR_CHAR && str[i] != ' ' &&
        str[i] != '\t') {
            nb_words++;
            new_word = 0;
        }
        if (str[i] == ' ' || str[i] == SEPARATOR_CHAR || str[i] == '\t')
            new_word = 1;
    }
    return (nb_words);
}

static char **get_words_2(char **arr, int nb_words)
{
    arr[nb_words] = NULL;
    for (int i = 0; arr[i] != NULL; i++)
        for (int j = 1; arr[i][j] != '\0' && arr[i][j-1] != '\0'; j++)
            if (arr[i][j] == ' ' || arr[i][j] == SEPARATOR_CHAR || arr[i][j] \
== '\t')
                arr[i][j] = '\0';
    return (arr);
}

char **get_words(char *str)
{
    char **arr = malloc(sizeof(char *) * (find_nb_words(str) + 1));
    int nb_words = 0;
    int new_word = 1;
    int i = 0;

    if (arr == NULL || str == NULL)
        return (NULL);
    for (; str[i] == '\t' || str[i] == ' '; i++);
    for (; str[i] != '\0'; i++) {
        if (new_word == 1 && str[i] != SEPARATOR_CHAR && str[i] != '\t' &&
        str[i] != ' ') {
            arr[nb_words] = &str[i];
            nb_words++;
            new_word = 0;
        }
        if (str[i] == ' ' || str[i] == SEPARATOR_CHAR || str[i] == '\t')
            new_word = 1;
    }
    get_words_2(arr, nb_words);
    return (arr);
}
