/*
** EPITECH PROJECT, 2018
** my_erasestr.c
** File description:
** erase str
*/

char *my_erasestr(char *str)
{
    int i = 0;

    for (; str[i+1] != 0; i++);
    for (; i >= 0; i--)
        str[i] = 0;
    return (str);
}
