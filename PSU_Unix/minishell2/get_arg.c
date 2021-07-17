/*
** EPITECH PROJECT, 2019
** get_arg
** File description:
** get the arg of shell
*/

#include "my.h"

arg_t *get_param(char **param)
{
    arg_t *arg = malloc(sizeof(arg_t));

    arg->next = NULL;
    arg->input = NULL;
    arg->output = NULL;
    arg->arg = param;
    arg->link = 0;
    return (arg);
}

void get_each_arg(shell_t *sh, char **param)
{
    char *separator[6] = {";", "|", ">", ">>", "<", "<<"};    

    for (int i = 0; i != 6; i++)
        if (!my_strcmp(param[0], separator[i])) {
            if (i / 2 == 0) {
                sh->arg->next = get_param(&param[1]);
                sh->arg->link = i % 2;
            } else if (i / 2 == 1) {
                sh->arg->output = get_param(&param[1]);
                sh->arg->output->link = i % 2;
            } else {
                sh->arg->input = get_param(&param[1]);
                sh->arg->input->link = i % 2;
            }
            if (i < 2)
                sh->arg = sh->arg->next;
            param[0] = NULL;
            return;
        }
    sh->arg = get_param(param);
}

void get_arg(shell_t *sh)
{
    arg_t *save = NULL;
    char *separator[6] = {";", "|", ">", "<", ">>", "<<"};

    sh->arr = get_words(get_next_line(0));
    if (!sh->arr)
        return;
    for (int i = 0; sh->arr[i];) {
        get_each_arg(sh, &sh->arr[i]);
        if (i == 0)
            save = sh->arg;
        else
            i++;
        for (int j = 0; sh->arr[i] && j != -1; j++)
            if (j == 6) {
                i++;
                j = -1;
            } else if (!my_strcmp(sh->arr[i], separator[j]))
                j = -2;
    }
    sh->arg = save;
}
