/*
** EPITECH PROJECT, 2019
** my_strncmp.c
** File description:
** Created by etienne-miltgen,
*/

int my_strncmp(const char *s1, const char *s2, int n)
{
    while (n != 0 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        (s1)++;
        (s2)++;
        n--;
    }
    if (n == 0)
        return (0);
    else
        return (*s1 - *s2);
}