/*
** EPITECH PROJECT, 2020
** main
** File description:
** main of menger sponge
*/

#include "menger.h"
#include "bitmap.h"
#include "drawing.h"

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

int match(char const *s1, char const *s2)
{
    while (s1[0] != '\0' && s2[0] != '\0'){
        if (s1[0] == s2[0])
            return (match(&s1[1], &s2[1]));
        if (s2[0] == '*')
            return (match(&s1[1], &s2[1]) || match(&s1[0], &s2[1]) |\
| match(&s1[1], &s2[0]));
        if (s1[0] != s2[0])
            return (0);
    }
    if (s1[0] == '\0' && s2[0] == '\0')
        return (1);
    else
        return (0);
}

int main(int n, char **arg)
{
    int len = 0;
    int recur = 0;

    if (n != 4) {
        dprintf(2, "%s file_name size level\n", arg[0]);
        return 84;
    }
    if (!match(arg[1], "*.bmp") || !isint(arg[2]) || !isint(arg[3]))
        return 84;
    len = atoi(arg[2]);
    recur = atoi(arg[3]);
    if (!isthirdlevel(len, recur))
        return 84;
    menger_face(arg[1], len, recur);
    return 0;
}