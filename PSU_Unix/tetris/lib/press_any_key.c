/*
** EPITECH PROJECT, 2019
** press_any_key.c
** File description:
** press any key
*/

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "my.h"

int set_read_mode(int mode)
{
    static struct termios termsave;
    static struct termios term;

    if (mode == 1) {
        if (ioctl(0, TCGETS, &term) == -1 || ioctl(0, TCGETS, &termsave) == -1)
            return (1);
        term.c_lflag &= ~ECHO;
        term.c_lflag &= ~ICANON;
        term.c_cc[VMIN] = 1;
        term.c_cc[VTIME] = 0;
        if (ioctl(0, TCSETS, &term) == -1)
            return (1);
    } else {
        if (ioctl(0, TCSETS, &termsave) == -1)
            return (1);
    }
    return (0);
}

int press_any_key(void)
{
    if (set_read_mode(1) == 1)
        return (84);
    read(0, NULL, 1);
    if (set_read_mode(0) == 1)
        return (84);
    return (0);
}
