/*
** EPITECH PROJECT, 2020
** PSU_strace_2019 [WSL: Ubuntu]
** File description:
** main
*/

#include "ftrace.h"

static void child_process(int n, char **arg)
{
    for (int i = 0; i != n-1; i++)
        arg[i] = arg[i+1];
    arg[n-1] = NULL;
    execvp(arg[0], arg);
}

int main(int n, char **arg)
{
    ftrace_t ftrace = {0};

    if (n < 2)
        return 84;
    if (!strcmp(arg[1], "-s")) {
        ftrace.display = true;
        arg++;
        n--;
    }
    if (!strcmp(arg[1], "-p") && n == 3 && strspn(arg[2], "0123456789") ==
        strlen(arg[2]))
        ftrace.pid = atoi(arg[2]);
    else
        ftrace.pid = fork();
    if (ftrace.pid == -1)
        return 84;
    else if (ftrace.pid == 0)
        child_process(n, arg);
    else
        parent_process(&ftrace);
}
