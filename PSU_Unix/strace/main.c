/*
** EPITECH PROJECT, 2020
** PSU_strace_2019 [WSL: Ubuntu]
** File description:
** main
*/

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void parent_process(int pid, bool display);
void child_process(int n, char **arg);

int main(int n, char **arg)
{
    bool display = false;
    int pid = 0;

    if (n < 2)
        return 84;
    if (!strcmp(arg[1], "-s")) {
        display = true;
        arg++;
        n--;
    }
    if (!strcmp(arg[1], "-p") && n == 3 && strspn(arg[2], "0123456789") ==
        strlen(arg[2]))
        pid = atoi(arg[2]);
    else
        pid = fork();
    if (pid == -1)
        return 84;
    else if (pid == 0)
        child_process(n, arg);
    else
        parent_process(pid, display);
}