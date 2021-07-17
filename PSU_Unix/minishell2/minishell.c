/*
** EPITECH PROJECT, 2019
** minishell
** File description:
** d
*/

#include "my.h"

void free_arg(shell_t *sh)
{
    arg_t *arg;

    my_close(&sh->in_pid[0]);
    my_close(&sh->out_pid[1]);
    for (; sh->arg; sh->arg = arg) {
        arg = sh->arg->next;
        if (sh->arg->input)
            free(sh->arg->input);
        if (sh->arg->output)
            free(sh->arg->output);
        free(sh->arg);
    }
    free(sh->arr[0]);
    free(sh->arr);
}

void print_start(void)
{
    char *filepath = getcwd(NULL, 0);
    char *str = filepath;
    char *prompt;

    for (int i = 0; filepath[i] != '\0'; i++)
        if (filepath[i] == '/')
            str = &filepath[i+1];
    prompt = string("[%sminishell%s %s%s%s]$> ", ROSE, RESET, YELLOW, (str && str[0]) \
? str : "/", RESET);
    my_printf("%s", prompt);
    free(filepath);
    free(prompt);
}

void minishell(shell_t *sh)
{
    arg_t *arg;

    print_start();
    sh->nb_process = 0;
    get_arg(sh);
    if (!sh->arr)
        my_exit(sh);
    arg = sh->arg;
    for (; sh->arg; sh->arg = sh->arg->next)
        execute(sh);
    sh->arg = arg;
    free_arg(sh);
}