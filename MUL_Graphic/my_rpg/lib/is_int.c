/*
** EPITECH PROJECT, 2018
** my_str_isnum.c
** File description:
** Return if the string is only composed of number.
*/

int is_int(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] > '9' || str[i] < '0')
            return (0);
    return (1);
}