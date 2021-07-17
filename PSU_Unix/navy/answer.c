/*
** EPITECH PROJECT, 2019
** answer
** File description:
** give and wait answer
*/

#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "navy.h"
#include "my.h"

void change_answer(int signal)
{
    if (signal == SIGUSR1) {
        get_answer('x');
    } else if (signal == SIGUSR2) {
        get_answer('o');
    }
}

char get_answer(int a)
{
    static char i = 0;

    i = a;
    if (a != 0) {
        i = a;
        return (0);
    }
    signal(SIGUSR1, &change_answer);
    signal(SIGUSR2, &change_answer);
    while (i == 0)
        usleep(5000);
    return (i);
}

void set_answer(int pid, int shot)
{
    if (shot == 1)
        kill(pid, SIGUSR1);
    if (shot == 0)
        kill(pid, SIGUSR2);
}
/*
int main(int n, char **arg)
{
    if (n != 4) return (84);
    my_printf("PID: %d\n", getpid());
    if (my_getnbr(arg[1]) == 1)
        set_answer(my_getnbr(arg[3]), my_getnbr(arg[2]));
    else
        my_printf("%c\n", get_answer(0));
}
*/
