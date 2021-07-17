/*
** EPITECH PROJECT, 2019
** label
** File description:
** comm
*/

#include "my.h"

void label(asm_t *r, char *str)
{
    int i = 0;
    char **tab = get_words(str);

    if (tab == NULL)
        return;
    r->other = 0;
    r->label = cpy_label(str);
    r->arg = cpy_com(str);
    for (i = 1; tab[i] != NULL; i++);
    r->param = malloc(sizeof(char *) * (i + 1));
    if (r->param == NULL) {
        free(tab);
        return;
    }
    for (i = 1; tab[i] != NULL; i++)
        r->param[i-1] = tab[i];
    r->param[i-1] = NULL;
    free(tab);
}

void com(asm_t *r, char *str)
{
    int i = 0;
    char **tab = get_words(str);

    r->other = 0;
    r->arg = my_strcpy_not_unsigned(tab[0]);
    for (i = 1; tab[0] && tab[i] != NULL; i++);
    r->param = malloc(sizeof(char *) * (i + 1));
    if (r->param == NULL) {
        free(tab);
        return;
    }
    for (i = 1; tab[0] && tab[i] != NULL; i++)
        r->param[i-1] = tab[i];
    r->param[i-1] = NULL;
    free(tab);
}
