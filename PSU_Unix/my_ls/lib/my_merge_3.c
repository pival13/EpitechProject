/*
** EPITECH PROJECT, 2019
** my_merge_3
** File description:
** merge three string
*/

#include <stdlib.h>

int my_strlen(char const *str);

char *my_merge(char const *s1, char const *s2, char const *s3)
{
    int a = my_strlen(s1);
    int b = my_strlen(s2);
    int c = my_strlen(s3);
    char *str;

    str = malloc(sizeof(char) * (a + b + c + 1));
    if (str == NULL)
        return (NULL);
    for (int i = 0; i < a; i++)
        str[i] = s1[i];
    for (int i = 0; i < b; i++)
        str[a+i] = s2[i];
    for (int i = 0; i < c; i++)
        str[a+b+i] = s3[i];
    str[a+b+c] = '\0';
    return (str);
}
