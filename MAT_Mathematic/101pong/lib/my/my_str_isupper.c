/*
** EPITECH PROJECT, 2018
** my_strisupper.c
** File description:
** Function that verify if only uppercase.
*/

int my_str_isupper(char const *str)
{
    int isupper = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] > 'Z' || str[i] < 'A')
            isupper = 1;
    }
    if (isupper == 1) {
        return (0);
    } else {
        return (1);
    }
}
