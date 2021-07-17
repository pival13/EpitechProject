/*
** EPITECH PROJECT, 2018
** my_sort_list_t
** File description:
** Sort an int array in ascending order.
*/

#include <stdlib.h>
#include <sys/stat.h>
#include "my_ls.h"

int my_strcmp(char const *s1, char const *s2);

list_t *my_sort_list_time(list_t *list)
{
    char *mem;
    struct stat smem;

    for (int i = 1; list[i].file != NULL;) {
        if (i == 0)
            i++;
        if (list[i].s.st_mtime > list[i-1].s.st_mtime || (list[i].s.st_mtime \
== list[i-1].s.st_mtime && list[i].s.st_mtim.tv_nsec > list[i-1].s.st_mtim.\
tv_nsec)) {
            mem = list[i-1].file;
            smem = list[i-1].s;
            list[i-1].file = list[i].file;
            list[i-1].s = list[i].s;
            list[i].file = mem;
            list[i].s = smem;
            i--;
        } else
            i++;
    }
    return (list);
}

list_t *my_sort_list_stat(list_t *list)
{
    char *mem;
    struct stat smem;

    if (list[0].file == NULL)
        return (list);
    for (int i = 1; list[i].file != NULL;) {
        if (i < 1)
            i = 1;
        if (my_strcmp(list[i].file, list[i-1].file) < 0) {
            mem = list[i-1].file;
            smem = list[i-1].s;
            list[i-1].file = list[i].file;
            list[i-1].s = list[i].s;
            list[i].file = mem;
            list[i].s = smem;
            i--;
        } else
            i++;
    }
    return (list);
}

list_t *my_sort_list_rev(list_t *list)
{
    char *mem;
    struct stat smem;
    int size = 0;

    for (; list[size].file != NULL; size++);
    size--;
    for (int i = 0; i < size / 2; i++) {
        mem = list[i].file;
        smem = list[i].s;
        list[i].file = list[size-i].file;
        list[i].s = list[size-i].s;
        list[size-i].file = mem;
        list[size-i].s = smem;
    }
    return (list);
}
