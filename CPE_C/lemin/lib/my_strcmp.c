/*
** EPITECH PROJECT, 2018
** my_strcmp
** File description:
** Compare the first letter of two string
*/

#include "my.h"
#include "lemin.h"

int my_strcmp_ci_end(char const *s1, char const *s2)
{
    int i = 0;
    for (; s1[i] != '\0'; i++);
    for (; s1[i] != '-' && i != 0; i--);
    i++;
    for (int k = 0; s1[i] != '\0'; i++, k++) {
        if (s1[i] != s2[k])
            return (1);
    }
    return (0);
}

int my_strcmp_ci(char const *s1, char const *s2)
{
    int i = 0;

    for (; s1[i] != '-' && s1[i] != '\0'; i++) {
        if (s1[i] != s2[i])
            return (1);
    }
    return (0);
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    if (my_strlength(s1) != my_strlength(s2))
        return (1);
    for (; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] != s2[i])
            return (1);
    }
    return (0);
}
