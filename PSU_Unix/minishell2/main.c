/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of minishell2
*/

#include "my.h"

void create_shell(shell_t *sh, char **env)
{
    int i = 0;

    for (; env && env[i]; i++);
    sh->env = malloc(sizeof(char *) * (i+1));
    for (int j = 0; sh->env && j != i; j++)
        sh->env[j] = string("%s", env[j]);
    sh->env[i] = NULL;
    sh->status = 0;
    sh->in_pid[0] = -1;
    sh->in_pid[1] = -1;
    sh->out_pid[0] = -1;
    sh->out_pid[1] = -1;
}

int main(int n, char **arg, char **env)
{
    shell_t shell;

    if (n != 1 || !arg)
        return (84);
    create_shell(&shell, env);
    while (1)
        minishell(&shell);
}