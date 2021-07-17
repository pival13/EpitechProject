/*
** EPITECH PROJECT, 2019
** count_nb_file
** File description:
** count the number of file in a delivery
*/

#include "my.h"
#include "my_ls.h"

int find_nb_file(char *str)
{
    DIR *dir = opendir(str);
    int i = 0;

    while (readdir(dir) != NULL)
        i++;
    closedir(dir);
    return (i);
}
