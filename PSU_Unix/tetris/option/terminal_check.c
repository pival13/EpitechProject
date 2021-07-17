/*
** EPITECH PROJECT, 2019
** terminal_check.c
** File description:
** terminal check for errors
*/

#include "my.h"

char *set_term_value(char *term)
{
    char *value = NULL;

    if (my_strlen(term) <= 5)
        return (NULL);
    value = malloc(sizeof(char) * (my_strlen(term) + 1));
    for (int i = 5, j = 0; term[i] != 0; i++, j++)
        value[j] = term[i];
    return (value);
}

int term_check(char **env)
{
    char *term = NULL;
    char *value = NULL;
    int error = 0;

    if (env == NULL || env[0] == NULL || env[0][0] == 0)
        return (84);
    for (int i = 0; env != NULL && env[i] != NULL && term == NULL; i++) {
        if (my_strcmp_begin(env[i], "TERM=") == 0)
            term = my_strcpy(env[i]);
    }
    if (term == NULL)
        return (84);
    value = set_term_value(term);
    (value == NULL) ? (error = 84) : (0);
    if (error != 84 && my_strcmp(value, "vt200") != 0 &&
        my_strcmp(value, "vt52") != 0 && my_strcmp_begin(value, "xterm") != 0)
        error = 84;
    free(term);
    free(value);
    return (error);
}
