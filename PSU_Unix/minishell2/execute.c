/*
** EPITECH PROJECT, 2019
** execute
** File description:
** execute the funct
*/

#include "my.h"

int execute_funct(shell_t *sh, char *str)
{
    int pid = 0;

    if (access(str, X_OK) == 0) {
        pid = fork();
        if (pid == 0) {
            my_close(&sh->out_pid[1]);
            execve(str, sh->arg->arg, sh->env);
            exit(0);
        } else
            wait(&sh->status);
        if (WIFSIGNALED(sh->status))
            my_dprintf(2, "%s.\n", strsignal(WTERMSIG(sh->status)));
        return (1);
    }
    return (0);
}

void check_line(shell_t *sh)
{
    char *str;
    char **path = get_var_env(sh->env, "PATH=");

    for (int i = 0; path && path[i]; i++) {
        str = string("%s/%s", path[i], sh->arg->arg[0]);
        if (execute_funct(sh, str)) {
            free(str);
            free(path[0]);
            free(path);
            return;
        }
        free(str);
    }
    my_printf("%s: Command not found.\n", sh->arg->arg[0]);
    sh->status = 127;
    if (path && path[0]) {
        free(path[0]);
        free(path);
    }
}

void exec(shell_t *sh)
{
    char *fun[5] = {"cd", "exit", "env", "setenv", "unsetenv"};
    void (*funct[5])(shell_t *) = {my_cd, my_exit, my_env, my_setenv, my_unsetenv};
    
    for (int i = 0; sh->arg && i != 5; i++)
        if (!my_strcmp(sh->arg->arg[0], fun[i]))
            return ((*funct[i])(sh));
    if (!execute_funct(sh, sh->arg->arg[0]))
        check_line(sh);
}

void wait_exec(shell_t *sh)
{
    my_close(&sh->in_pid[0]);
    my_close(&sh->out_pid[1]);
    if (sh->arg->link == 1)
        sh->nb_process++;
    else {
        for (int i = 0; i <= sh->nb_process; sh->nb_process--) {
            wait(&sh->status);
            sh->status = WEXITSTATUS(sh->status);
        }
        sh->nb_process = 0;
    }
    sh->in_pid[0] = sh->out_pid[0];
    sh->out_pid[0] = -1;
}

void execute(shell_t *sh)
{
    int pid; 

    if (my_strcmp("cd", sh->arg->arg[0]) && my_strcmp("exit", sh->arg->arg[0])) {
        if (sh->arg->link == 1)
            pid = pipe(sh->out_pid);
        pid = fork();
        if (pid == 0) {
            my_close(&sh->out_pid[0]);
            make_pipe(sh);
            exec(sh);
            my_close(&sh->in_pid[0]);
            my_close(&sh->out_pid[1]);
            exit(sh->status);
        } else
            wait_exec(sh);
    } else 
        exec(sh);
}