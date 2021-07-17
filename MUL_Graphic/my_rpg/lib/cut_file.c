/*
** EPITECH PROJECT, 2019
** read_file
** File description:
** read a file with GNL
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd);

static int length_file(char *filepath)
{
    char *line;
    int fd = open(filepath, O_RDONLY);
    int i = 0;

    if (fd == -1)
        return (0);
    line = get_next_line(fd);
    for (; line != NULL; i++) {
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (i);
}

static int find_nb_words(char *str)
{
    int nb_words = 1;

    for (int i = 0; str != NULL && str[i] != '\0'; i++) {
        if (str[i] == ',')
            nb_words++;
    }
    return (nb_words);
}

static char **get_word_2(char **arr, int new, int nb, char *str)
{
    int len = 0;

    for (; str[len] != '\0'; len++);
    if (new == 1) {
        arr[nb] = &str[len];
        arr[nb+1] = NULL;
    } else
        arr[nb] = NULL;
    for (int i = 0; arr[i] != NULL; i++)
        for (int j = 0; arr[i][j] != '\0'; j++)
            (arr[i][j] == ',') ? (arr[i][j] = '\0') : (0);
    return (arr);
}

static char **get_word(char *str)
{
    char **arr = malloc(sizeof(char *) * (find_nb_words(str) + 1));
    int nb_words = 0;
    int new_word = 1;

    if (arr == NULL || str == NULL)
        return (NULL);
    for (int i = 0; str[i] != '\0'; i++) {
        if (new_word == 1) {
            arr[nb_words] = &str[i];
            nb_words++;
            new_word = 0;
        }
        if (str[i] == ',')
            new_word = 1;
    }
    arr = get_word_2(arr, new_word, nb_words, str);
    return (arr);
}

char ***cut_file(char *filepath)
{
    int length = length_file(filepath) + 1;
    int fd = open(filepath, O_RDONLY);
    char ***map;

    if (fd == -1)
        return (NULL);
    map = malloc(sizeof(char **) * length);
    for (int i = 0; map != NULL; i++) {
        map[i] = get_word(get_next_line(fd));
        if (map[i] == NULL)
            break;
    }
    close(fd);
    return (map);
}
