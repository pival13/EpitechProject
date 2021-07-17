/*
** EPITECH PROJECT, 2019
** game.c
** File description:
** game itself functions
*/

#include "my.h"
#include "navy.h"
#include <unistd.h>

int end_game(arrays_t *arrays)
{
    print_navy(arrays);
    if (arrays->nb_deaths >= 14) {
        my_printf("Enemy won\n");
        return (1);
    } else if (arrays->nb_kills >= 14) {
        my_printf("I won\n");
        return (0);
    } else
        return (0);
}

int game(char **pos, int id_player, int pid_other)
{
    arrays_t *arrays = create_arrays();

    arrays = trad_arrays(arrays, pos);
    if (arrays == NULL) return (84);
    my_printf("my_pid: %d\n", getpid());
    if (id_player == 1)
        my_printf("waiting for enemy connection...\n\n");
    pid_other = get_other_pid(pid_other, id_player);
    if (id_player == 1) my_printf("enemy connected\n\n");
    else my_printf("successfully connected\n\n");
    while (is_end(&arrays) == 0) {
        print_navy(arrays);
        if (id_player == 1) order(arrays, pid_other);
        if (is_end(&arrays) != 0) break;
        enemy_attack(arrays, pid_other);
        if (is_end(&arrays) != 0) break;
        if (id_player == 2) order(arrays, pid_other);
    }
    return (end_game(arrays));
}
