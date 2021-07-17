/*
** EPITECH PROJECT, 2019
** get_signal
** File description:
** get signals send
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "my.h"
#include "navy.h"

void change_int(int a, int *nb1, int *nb2)
{
    static int sig[2] = {0, 0};

    if (a == 1)
        sig[0]++;
    else if (a == 2)
        sig[1]++;
    else {
        *nb1 = sig[0];
        *nb2 = sig[1];
        sig[0] = 0;
        sig[1] = 0;
    }
}

void sig(int signal)
{
    static int i = 0;

    if (signal == SIGUSR1) {
        if (i == 0)
            change_int(1, NULL, NULL);
        else if (i == 1)
            change_int(2, NULL, NULL);
    }
    if (signal == SIGUSR2)
        i++;
    if (i >= 2) {
        i = 0;
        get_signal(NULL, NULL, 1);
    }
}

void get_signal(int *a, int *b, int c)
{
    static int i = 0;

    if (c == 0) {
        *a = 0;
        *b = 0;
        signal(SIGUSR1, &sig);
        signal(SIGUSR2, &sig);
        i = 0;
        while (i == 0)
            pause();
        change_int(0, a, b);
    } else {
        i = 1;
    }
}
/*
int main(void)
{
    int a = 0;
    int b = 0;

    my_printf("PID: %d\n", getpid());
    while (1) {
        get_signal(&a, &b, 0);
        my_printf("%d %d\n", a, b);
    }
}
*/
