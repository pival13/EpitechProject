/*
** EPITECH PROJECT, 2018
** infin_div
** File description:
** Calculate an infinite division from two given arguments
*/

#include "../../include/my.h"
#include <stdlib.h>

int check_error(char *av1, char *av2)
{
    if (av2[0] == '0')
        exit(0);
    else if (av2[0] == '1' && av2[1] == '\0' || av1[0] == '0')
        return (0);
    return (48);
}

char *sign_division(char *tf1)
{
    char *m6 = malloc(sizeof(char)*(my_strlen(tf1) + 1));
    int a = 0;

    for (int i = 0; tf1[i] != 0; i++) {
        if (tf1[i] == '-' && a == 0)
            a = 1;
        else if (tf1[i] == '-' && a == 1)
            a = 0;
    }
    if (a == 1)
        m6[0] = '-';
    for (int i = 0; tf1[i] != 0; i++) {
        if ('0' <= tf1[i] && tf1[i] <= '9') {
            m6[a] = tf1[i];
            a++;
        }
    }
    return (m6);
}

int compar(char *av1, char *av2)
{
    if (my_strlen(av1) > my_strlen(av2))
        return (0);
    else if (my_strlen(av1) < my_strlen(av2))
        return (1);
    for (int a = 0; av1[a] != '\0'; a++) {
        if (av1[a] > av2[a])
            return (0);
        else if (av1[a] < av2[a])
            return (1);
    }
    return (0);
}

char *infin_div(char *av1, char *av2)
{
    char *divisorm = av2;
    char *result = "0";
    char *mult = "1";

    if (check_error(av1, av2) == 0)
        return (av1);
    for (; compar(av1, av2) == 0;) {
        while (my_strlen(divisorm) + 1 < my_strlen(av1)) {
            divisorm = infin_mult(divisorm, "10");
            mult = infin_mult(mult, "10");
        } if (compar(av1, divisorm) == 1) {
            divisorm = av2;
            mult = "1";
        }
        while (compar(av1, divisorm) == 0) {
            av1 = infin_sub(av1, divisorm);
            result = infin_add(result, mult);
        }
    }
    return (result);
}
