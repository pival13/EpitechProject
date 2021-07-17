/*
** EPITECH PROJECT, 2019
** enemy_attack
** File description:
** wait for enemy attack
*/

#include "my.h"
#include "navy.h"
#include <unistd.h>

int check_shot(arrays_t *arrays, int a, int b)
{
    my_printf("%c%d: ", a + 'A' - 1, b);
    if (arrays->p1[b][a] == '.') {
        arrays->p1[b][a] = 'o';
        my_putstr("missed\n\n");
        return (0);
    } else if (arrays->p1[b][a] == 'o' || arrays->p1[b][a] == 'x') {
        my_putstr("missed\n\n");
        return (0);
    } else {
        arrays->p1[b][a] = 'x';
        my_putstr("hit\n\n");
        return (1);
    }
}

void enemy_attack(arrays_t *arrays, int pid_other)
{
    int a;
    int b;
    char c = 'o';

    my_putstr("waiting for enemy's attack...\n");
    while (c == 'o') {
        get_signal(&a, &b, 0);
        usleep(5000);
        send_signal(pid_other, a, b);
        c = get_answer(0);
        usleep(5000);
    }
    set_answer(pid_other, check_shot(arrays, a, b));
}
