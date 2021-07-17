/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of assembleur
*/

#include "my.h"

static void free_list(asm_t *list)
{
    asm_t *next = NULL;

    for (; list != NULL; list = next) {
        next = list->next;
        if (list->other == 0) {
            (list->label != NULL) ? free(list->label) : (0);
            free(list->param);
        }
        if (list->other >= 0)
            free(list->arg);
        free(list);
    }
}

static void free_file(char **file)
{
    if (file) {
        for (int i = 0; file[i] != NULL; i++)
            free(file[i]);
        free(file);
    }
}

int main(int n, char **arg)
{
    char **file;
    asm_t *list;

    if (n != 2)
        return (84);
    file = read_file(arg[1]);
    if (file == NULL || file[0] == NULL) {
        free_file(file);
        return (84);
    }
    list = parsing(file);
    if (!list || check_file(list) == 84) {
        free_list(list);
        free_file(file);
        return (84);
    }
    assembler(list, arg[1]);
    free_list(list);
    free_file(file);
    return (0);
}