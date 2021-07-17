/*
** EPITECH PROJECT, 2019
** read_file
** File description:
** read a file with GNL
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

static int length_file(char *filepath)
{
    char *line;
    int fd = open(filepath, O_RDONLY);
    int i = 0;

    if (fd == -1)
        return (0);
    line = get_next_line(fd);
    for (; line != NULL;) {
        if (line[0] != COMMENT_CHAR)
            i++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (i);
}

static int find_nb_words(char *str)
{
    int nb_words = 0;
    int new_word = 1;

    for (int i = 0; str != NULL && str[i] != '\0'; i++) {
        if (new_word == 1 && (str[i] != SEPARATOR_CHAR || str[i] != ' ')) {
            nb_words++;
            new_word = 0;
        }
        if (str[i] == SEPARATOR_CHAR || str[i] == ' ')
            new_word = 1;
    }
    return (nb_words);
}

static char **get_word_2(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        for (int j = 1; arr[i][j] != '\0' && arr[i][j-1] != '\0'; j++)
            if (arr[i][j] == SEPARATOR_CHAR || arr[i][j] == ' ')
                arr[i][j] = '\0';
    return (arr);
}

static char **get_word(char *str)
{
    char **arr = NULL;
    int nb_words = 0;
    int new_word = 1;

    arr = malloc(sizeof(char *) * (find_nb_words(str) + 1));
    if (arr == NULL || str == NULL)
        return (NULL);
    for (int i = 0; str[i] != '\0'; i++) {
        if (new_word == 1 && (str[i] != SEPARATOR_CHAR || str[i] != ' ')) {
            arr[nb_words] = &str[i];
            nb_words++;
            new_word = 0;
        }
        if (str[i] == SEPARATOR_CHAR || str[i] == ' ')
            new_word = 1;
    }
    arr[nb_words] = NULL;
    arr = get_word_2(arr);
    return (arr);
}

char ***cut_file(char *filepath)
{
    int length = length_file(filepath) + 1;
    int fd = open(filepath, O_RDONLY);
    char ***map;

    map = malloc(sizeof(char **) * length);
    if (map == NULL || fd == -1)
        return (NULL);
    for (int i = 0; map != NULL; i++) {
        map[i] = get_word(get_next_line(fd));
        if (map[i] == NULL)
            break;
        if (map[i][0] != NULL && map[i][0][0] == COMMENT_CHAR) {
            free(map[i][0]);
            free(map[i]);
            map[i] = NULL;
            i--;
        }
    }
    close(fd);
    return (map);
}