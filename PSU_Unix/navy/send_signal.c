/*
** EPITECH PROJECT, 2019
** send_signal
** File description:
** send two numbers with signals
*/

#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "my.h"
#include "navy.h"

void send_signal(int pid, int a, int b)
{
    for (int i = 0; i != a; i++) {
        kill(pid, SIGUSR1);
        usleep(5000);
    }
    usleep(10000);
    kill(pid, SIGUSR2);
    usleep(10000);
    for (int i = 0; i != b; i++) {
        kill(pid, SIGUSR1);
        usleep(5000);
    }
    kill(pid, SIGUSR2);
}
/*
int main(int n, char **arg)
{
    if (n != 4) return (84);
    send_signal(my_getnbr(arg[1]), my_getnbr(arg[2]), my_getnbr(arg[3]));
    my_printf("Signals send\n");
}
*/
