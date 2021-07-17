/*
** EPITECH PROJECT, 2020
** Created by theo on 30/04/2020.
** File description:
** main.c
*/

#include "my.h"

void my_free(void *ptr)
{
    if (ptr != NULL)
        free(ptr);
    return;
}


void *my_malloc(int size)
{
    void *new = malloc(size);

    if (new == NULL) {
        perror("Unable to allocate memory");
        exit(EXIT_FAILURE);
    }
    return new;
}

bool is_end(bool i)
{
    static bool value = false;

    if (value == true)
        exit(84);
    if (i)
        value = true;
    return value;
}

void sig_handler(int sig)
{
    signal(sig, SIG_IGN);
    printf("Exiting Program\n");
    is_end(true);
    signal(SIGINT, sig_handler);
}

int main(int ac, char **av)
{
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    if (strcmp("-help", av[1]) == 0) {
        printf("USAGE: ./zappy_server -p port -x width -y height"
               "-n name1 name2 ... -c clientsNb\n"
               "-f freq\n"
               "\tport      is the port number\n"
               "\twidth     is the width of the world\n"
               "\theight    is the height of the world\n"
               "\tnameX     is the name of the team X\n"
               "\tclientsNb is the number of authorized clients per team\n"
               "\tfreq      is the reciprocal of time unit for execution of"
               "actions\n");
        return 0;
    }
    return init_games(ac, av);
}