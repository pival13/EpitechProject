/*
** EPITECH PROJECT, 2020
** mem_ptr.c
** File description:
** mem ptr
*/

#include "mem_ptr.h"
#include <stdlib.h>
#include <string.h>

void add_str(const char *str1, const char *str2, char **res)
{
    int len1 = 0;
    int len2 = 0;

    if (str1 != NULL)
        len1 = strlen(str1);
    if (str2 != NULL)
        len2 = strlen(str2);
    *res = malloc(sizeof(char) * (len1 + len2 + 1));
    if (*res == NULL)
        return;
    for (int i = 0; i < len1; i++)
        res[0][i] = str1[i];
    for (int i = 0; i < len2; i++)
        res[0][len1+i] = str2[i];
    res[0][len1+len2] = '\0';
}

void add_str_struct(str_op_t *str)
{
    int len1 = 0;
    int len2 = 0;

    if (str->str1 != NULL)
        len1 = strlen(str->str1);
    if (str->str2 != NULL)
        len2 = strlen(str->str2);
    str->res = malloc(sizeof(char) * (len1 + len2 + 1));
    if (str->res == NULL)
        return;
    for (int i = 0; i < len1; i++)
        str->res[i] = str->str1[i];
    for (int i = 0; i < len2; i++)
        str->res[len1+i] = str->str2[i];
    str->res[len1+len2] = '\0';
}