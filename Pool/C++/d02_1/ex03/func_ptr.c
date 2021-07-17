/*
** EPITECH PROJECT, 2020
** func_ptr
** File description:
** print a string depending the function
*/

#include "func_ptr.h"

void print_normal(const char *str)
{
    if (str == NULL)
        return;
    printf("%s\n", str);
}

void print_reverse(const char *str)
{
    if (str == NULL)
        return;
    for (int i = strlen(str) - 1; i >= 0; i--)
        putchar(str[i]);
    putchar('\n');
}

void print_upper(const char *str)
{
    if (str == NULL)
        return;
    for (unsigned int i = 0; i < strlen(str); i++)
        putchar(toupper(str[i]));
    putchar('\n');
}

void print_42(const char *str)
{
    if (str == NULL)
        return;
    printf("42\n");
}

void do_action(action_t action, const char *str)
{
    void (*funct[4])(const char *) = {
        print_normal,
        print_reverse,
        print_upper,
        print_42
    };

    if (action < 0 || action > 4)
        return;
    (*funct[action])(str);
}