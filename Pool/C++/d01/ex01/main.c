/*
** EPITECH PROJECT, 2020
** main
** File description:
** main of menger sponge
*/

#include "menger.h"

int isint(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return 1;
}

int isthirdlevel(int nb, int recur)
{
    while (nb > 1) {
        if (nb % 3 != 0)
            return 0;
        nb = nb / 3;
        recur--;
    }
    if (nb == 1 && recur <= 0)
        return 1;
    else
        return 0;
}

int main(int n, char **arg)
{
    int len = 0;
    int recur = 0;

    if (n != 3 || !isint(arg[1]) || !isint(arg[2]))
        return 84;
    len = atoi(arg[1]);
    recur = atoi(arg[2]);
    if (!isthirdlevel(len, recur))
        return 84;
    menger(len, recur, (int[2]){0, 0});
    return 0;
}