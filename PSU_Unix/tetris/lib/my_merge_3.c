/*
** EPITECH PROJECT, 2019
** my_merge_3
** File description:
** merge three string
*/

#include <stdlib.h>

static int my_strlength(char const *str)
{
    int i = 0;

    if (str == NULL) return (0);
    for (; str[i] != '\0'; i++);
    return (i);
}

char *my_merge_3(char const *s1, char const *s2, char const *s3)
{
    int a = my_strlength(s1);
    int b = my_strlength(s2);
    int c = my_strlength(s3);
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

char *my_fmerge_3(char *s1, char *s2, char *s3)
{
    int a = my_strlength(s1);
    int b = my_strlength(s2);
    int c = my_strlength(s3);
    char *str;

    str = malloc(sizeof(char) * (a + b + c + 1));
    if (str == NULL) return (NULL);
    for (int i = 0; i < a; i++)
        str[i] = s1[i];
    for (int i = 0; i < b; i++)
        str[a+i] = s2[i];
    for (int i = 0; i < c; i++)
        str[a+b+i] = s3[i];
    str[a+b+c] = '\0';
    if (s1 != NULL) free(s1);
    if (s2 != NULL) free(s2);
    if (s3 != NULL) free(s3);
    return (str);
}
