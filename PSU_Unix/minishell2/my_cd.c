/*
** EPITECH PROJECT, 2019
** my_funct
** File description:
** contain the function of minishell which must be recreate
*/

#include "my.h"

int change_directry(shell_t *sh)
{
    int err = 0;
    char *str = NULL;
    char *pwd = NULL;

    if (!sh->arg->arg[1] || !my_strcmp(sh->arg->arg[1], "~"))
        err = chdir(get_home(sh->env));
    else if (!my_strcmp(sh->arg->arg[1], "-"))
        err = chdir(get_oldpwd(sh->env));
    else
        if (sh->arg->arg[1][0] != '/') {
            pwd = getcwd(NULL, 0);
            str = string("%s/%s", pwd, sh->arg->arg[1]);
            err = chdir(str);
            free(pwd);
            free(str);
        } else
            err = chdir(sh->arg->arg[1]);
    return (err);
}

void my_cd(shell_t *sh)
{
    char *pwd = getcwd(NULL, 0);

    if (sh->arg->arg[1] && sh->arg->arg[2]) {
        my_printf("cd: Trop d'arguments.\n");
        sh->status = 1;
        return;
    }
    if (change_directry(sh) != 0) {
        sh->status = 1;
        my_printf("%s: %s.\n", sh->arg->arg[1], strerror(errno));
    } else {
        sh->status = 0;
        add_var(sh, "OLDPWD", pwd);
        free(pwd);
        pwd = getcwd(NULL, 0);
        add_var(sh, "PWD", pwd);
    }
    free(pwd);
}
