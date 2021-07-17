/*
** EPITECH PROJECT, 2019
** order.c
** File description:
** order funcs
*/

#include "navy.h"
#include "my.h"
#include <unistd.h>

char *less_msg(char *msg)
{
    if (my_strlen(msg) == 3)
        msg[2] = 0;
    for (int i = my_strlen(msg) - 1; i >= 3; i--) {
        msg[i-1] = msg[i];
        msg[i] = 0;
    }
    return (msg);
}

int order_verify(char *msg, arrays_t *arrays)
{
    for (; msg[0] == ' ' || msg[0] == '\t'; msg++);
    for (; msg[2] == ' ' || msg[2] == '\t'; msg = less_msg(msg));
    if (my_strlen(msg) != 2)
        return (84);
    if (msg[0] > 72 || msg[0] < 65)
        return (84);
    if (msg[1] > 56 || msg[1] < 49)
        return (84);
    if (arrays->p2[msg[1]-48][msg[0]-64] != '.')
        return (1);
    return (0);
}

void communication2(arrays_t *arrays, int a, int b)
{
    int mem = get_answer(0);

    my_printf("%c%c: ", a + 'A' - 1, b + '0');
    if (arrays->p2[b][a] == '.') {
        arrays->p2[b][a] = mem;
        if (arrays->p2[b][a] == 'x') {
            my_printf("hit\n\n");
            return;
        }
    }
    my_printf("missed\n\n");
}

void communication(arrays_t *arrays, int pid_other, int a, int b)
{
    int verif[2] = {0, 0};

    while (a != verif[0] || b != verif[1]) {
        send_signal(pid_other, a, b);
        get_signal(&verif[0], &verif[1], 0);
        usleep(5000);
        if (a == verif[0] && b == verif[1])
            set_answer(pid_other, 1);
        else
            set_answer(pid_other, 0);
    }
    communication2(arrays, a, b);
}

void order(arrays_t *arrays, int pid_other)
{
    int sent = 0;
    char *msg;
    int orders[2];

    while (sent == 0) {
        my_printf("attack: ");
        msg = get_next_line(0);
        if (order_verify(msg, arrays) != 84)
            sent = 1;
        if (sent == 0)
            my_printf("wrong position\n");
    }
    orders[0] = msg[0] - 64;
    orders[1] = msg[1] - 48;
    communication(arrays, pid_other, orders[0], orders[1]);
}
