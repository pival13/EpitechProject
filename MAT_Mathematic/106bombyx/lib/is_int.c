/*
** EPITECH PROJECT, 2018
** my_str_isnum.c
** File description:
** Return if the string is only composed of number.
*/

int is_int(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (i == 0 && (str[i] == '-' || (str[i] <= '9' && str[i] >= '0')))
            i++;
        else if (str[i] <= '9' && str[i] >= '0')
            i++;
        else
            return (0);
    }
    return (1);
}
