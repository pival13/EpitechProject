/*
** EPITECH PROJECT, 2019
** my_funct
** File description:
** contain the function of minishell which must be recreate
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "my.h"
#include "minishell.h"

void my_setenv(shell_t *sh)
{
    if (!sh->arg->arg[1])
        return (my_env(sh));
    if (sh->arg->arg[2] && sh->arg->arg[3]) {
        my_printf("setenv: Trop d'arguments.\n");
        sh->status = 1;
        return;
    } else if (!is_alphanum(sh->arg->arg[1])) {
        my_printf("setenv: Variable name must contain alphanumeric characters\
.\n");
        sh->status = 1;
        return;
    }
    add_var(sh, sh->arg->arg[1], sh->arg->arg[2]);
    sh->status = 0;
}

void my_unsetenv(shell_t *sh)
{
    if (sh->arg->arg[1] == NULL) {
        my_printf("unsetenv: Trop peu d'arguments.\n");
        sh->status = 1;
        return;
    }
    for (int j = 1; sh->arg->arg[j]; j++)
        del_var(sh, sh->arg->arg[j]);
    sh->status = 0;
}

void my_env(shell_t *sh)
{
    for (int i = 0; sh->env && sh->env[i]; i++)
        my_printf("%s\n", sh->env[i]);
    sh->status = 0;
}

void my_exit(shell_t *sh)
{
    my_printf("exit\n");
    if (sh->arr && sh->arg && sh->arg->arg && sh->arg->arg[0])
        free_arg(sh);
    for (int i = 0; sh->env && sh->env[i]; i++)
        free(sh->env[i]);
    free(sh->env);
    exit(sh->status);
}