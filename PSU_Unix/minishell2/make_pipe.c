/*
** EPITECH PROJECT, 2019
** make_pipe
** File description:
** link a programm with input or output
*/

#include "my.h"

void link_input(shell_t *sh)
{
    char *str;

    my_close(&sh->in_pid[0]);
    if (sh->arg->input->link == 0)
        sh->in_pid[0] = open(sh->arg->input->arg[0], O_RDONLY);
    else if (sh->arg->input->arg[0]) {
        if (pipe(sh->in_pid) == -1)
            return;
        str = get_next_line(0);
        while (my_strcmp(str, sh->arg->input->arg[0])) {
            my_dprintf(sh->in_pid[1], "%s\n", str);
            free(str);
            str = get_next_line(0);
        }
        my_close(&sh->in_pid[1]);
    }
}

void link_output(shell_t *sh)
{
    my_close(&sh->out_pid[1]);
    if (sh->arg->output->link == 0)
        sh->out_pid[1] = open(sh->arg->output->arg[0], O_WRONLY|O_CREAT|O_TRUNC, 0664);
    else
        sh->out_pid[1] = open(sh->arg->output->arg[0], O_WRONLY|O_CREAT|O_APPEND, 0664);
}

void make_pipe(shell_t *sh)
{
    if (sh->arg->input)
        link_input(sh);
    if (sh->arg->output)
        link_output(sh);
    if (sh->in_pid[0] != -1)
        dup2(sh->in_pid[0], 0);
    if (sh->out_pid[1] != -1)
        dup2(sh->out_pid[1], 1);
}
