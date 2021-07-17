/*
** EPITECH PROJECT, 2020
** Created by theo on 20/05/2020.
** File description:
** tools.c
*/

#include "my.h"

char *int_to_char(int nbr)
{
    int j = 0;
    char *str;
    int tmp = 0;

    for (int a = nbr; a >= 10; a /= 10) j++;
    str = my_malloc(sizeof(char) * (j + 3));
    for (int i = 0, k = 1; i <= j; i++) {
        for (int z = 0; z < i; k = k * 10, z++);
        tmp = nbr / k;
        for (; tmp >= 10; tmp -= 10);
        str[j - i] = tmp + 48;
    }
    str[j + 1] = '\n';
    str[j + 2] = '\0';
    return (str);
}

int my_strlen(const char *str)
{
    int i = 0;

    if (str == NULL) return 0;
    for (; str[i] != '\0'; i++);
    return i;
}

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char *my_strcat_second(char *res, char *ret)
{
    int j = my_strlen(res);
    int l = j + my_strlen(ret);

    res = realloc(res, l + 1);
    if (ret != NULL) {
        for (int i = 0; ret[i] != '\0'; i++, j++)
            res[j] = ret[i];
    }
    res[j] = '\0';
    return (res);
}

char *my_strcat(char *res, char *ret)
{
    int j = my_strlen(res);
    int l = j + my_strlen(ret);

    res = realloc(res, l + 1);
    if (ret != NULL) {
        for (int i = 0; ret[i] != '\0'; i++, j++)
            res[j] = ret[i];
        my_free(ret);
    }
    res[j] = '\0';
    return (res);
}