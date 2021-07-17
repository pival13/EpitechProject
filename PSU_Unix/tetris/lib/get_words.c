/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of sort_words
*/

#include <stdlib.h>
#include <unistd.h>

static int find_nb_words(char *str)
{
    int nb_words = 0;
    int new_word = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (new_word == 1 && str[i] != '\n') {
            nb_words++;
            new_word = 0;
        }
        if (str[i] == '\n')
            new_word = 1;
    }
    return (nb_words);
}

static char **get_words_2(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        for (int j = 1; arr[i][j] != '\0' && arr[i][j-1] != '\0'; j++)
            (arr[i][j] == '\n') ? (arr[i][j] = '\0') : (0);
    return (arr);
}

char **get_words(char *str)
{
    char **arr = malloc(sizeof(char *) * (find_nb_words(str) + 1));
    int nb_words = 0;
    int new_word = 1;

    if (arr == NULL || str == NULL || str[0] == '\0')
        return (NULL);
    for (int i = 0; str[i] != '\0'; i++) {
        if (new_word == 1 && str[i] != '\n') {
            arr[nb_words] = &str[i];
            nb_words++;
            new_word = 0;
        }
        if (str[i] == '\n')
            new_word = 1;
    }
    arr[nb_words] = NULL;
    get_words_2(arr);
    return (arr);
}
