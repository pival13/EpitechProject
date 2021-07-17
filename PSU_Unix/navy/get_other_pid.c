/*
** EPITECH PROJECT, 2019
** get_other_pid
** File description:
** get the pid of the second navy
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "navy.h"

void change_pid(int signal, siginfo_t *s, void *a)
{
    if (signal == SIGUSR1)
        get_other_pid(s->si_pid, -1);
    if (a == NULL) return;
}

int get_other_pid(int p, int player)
{
    struct sigaction s;
    static int pid = 0;

    if (player == -1) {
        pid = p;
        return (0);
    } else if (player == 2) {
        kill(p, SIGUSR1);
        p = 0;
    }
    s.sa_flags = SA_SIGINFO;
    s.sa_sigaction = &change_pid;
    sigaction(SIGUSR1, &s, NULL);
    while (pid == 0)
        usleep(5000);
    if (player == 1) kill(pid, SIGUSR1);
    return (pid);
}
/*
int main(int n, char **arg)
{
    int i = 0;

    if (n != 3) return (84);
    i = get_other_pid(my_getnbr(arg[2]), my_getnbr(arg[1]));
    my_printf("%d\n", i);
}

*/
