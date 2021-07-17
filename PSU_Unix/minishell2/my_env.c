/*
** EPITECH PROJECT, 2019
** my_env
** File description:
** interact with env
*/

#include "my.h"

void add_var(shell_t *sh, char *name, char *var)
{
    int i = 0;
    char **env;
    int size = 0;

    for (; name && name[size]; size++);
    for (; sh->env && sh->env[i] && !(!my_strncmp(sh->env[i], name, size) && sh->\
env[i][size] == '='); i++);
    if (sh->env && sh->env[i]) {
        free(sh->env[i]);
        sh->env[i] = string("%s=%s", name, var);
        return;
    }
    env = malloc(sizeof(char *) * (i+2));
    for (int j = 0; j != i; j++)
        env[j] = sh->env[j];
    env[i] = string("%s=%s", name, var);
    env[i+1] = NULL;
    free(sh->env);
    sh->env = env;
}

void del_var(shell_t *sh, char *name)
{
    int size = 0;
    int i = 0;

    for (; name && name[size]; size++);
    for (; sh->env && sh->env[i] && (my_strncmp(sh->env[i], name, size) || \
sh->env[i][size] != '='); i++);
    if (sh->env && sh->env[i]) {
        free(sh->env[i]);
        sh->env[i] = sh->env[i+1];
        for (int j = i+1; sh->env[j]; j++)
            sh->env[j] = sh->env[j+1];
    }
}
