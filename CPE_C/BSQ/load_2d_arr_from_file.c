/*
** EPITECH PROJECT, 2018
** load_2d_arr_from_file
** File description:
** Create a 2d array from an 1d array
*/

#include "my.h"
#include <stdlib.h>

char *load_file_in_memory(char const *);

char **load_2d_arr_from_file(char const *filepath)
{
    int j = 0;
    char *file = load_file_in_memory(filepath);
    char **array;
    int rows = 0;
    int cols = 0;

    for (int i = 0; file[i] != '\0'; i++)
        (file[i] == '\n') ? (rows++) : (rows);
    array = malloc(sizeof(char *) * rows + 2);
    for (int k = 0; file[k] != '\0'; j++, k++) {
        for (cols = 0; file[k+cols] != '\n' && file[k+cols] != '\0'; cols++);
        array[j] = malloc(sizeof(char) * (cols + 2));
        for (int i = 0; file[k] != '\n' && file[k+1] != '\0'; i++, k++)
            array[j][i] = file[k];
        my_strcat(array[j], "\n\0");
    }
    array[j] = NULL;
    free(file);
    return (array);
}
