/*
** EPITECH PROJECT, 2019
** test
** File description:
** test
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "navy.h"
#include "my.h"

Test(navy, signal)
{
    int other_pid = getpid();
    int pid = fork();
    int a = 0;
    int b = 0;

    if (pid == 0) {
        sleep(1);
        my_printf("Sender pid: %d\n", getpid());
        my_printf("Signals sent to %d\n", other_pid);
        send_signal(other_pid, 5, 2);
        return;
    } else {
        my_printf("Receiver pid: %d\n", getpid());
        my_printf("Wait signal\n");
        get_signal(&a, &b, 0);
        my_printf("Got signal %d %d\n", a, b);
        sleep(1);
    }
    cr_assert_eq(a, 5);
    cr_assert_eq(b, 2);
}
