/*
** EPITECH PROJECT, 2018
** my_sort_list
** File description:
** Sort an int array in ascending order.
*/

#include <stdlib.h>

int my_strcmp(char const *s1, char const *s2);

char **my_sort_list(char **array)
{
    char *mem;

    if (array[0] == NULL)
        return (array);
    for (int i = 1; array[i] != NULL;) {
        if (i == 0)
            i++;
        if (my_strcmp(array[i], array[i-1]) < 0) {
            mem = array[i - 1];
            array[i - 1] = array[i];
            array[i] = mem;
            i--;
        } else
            i++;
    }
    return (array);
}
