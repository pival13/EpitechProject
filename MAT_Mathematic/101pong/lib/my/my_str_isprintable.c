/*
** EPITECH PROJECT, 2018
** my_strisprintable.c
** File description:
** Function that verify if only uppercase.
*/

int my_str_isprintable(char const *str)
{
    int isprintable = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 32 || str[i] > 255)
            isprintable = 1;
    }
    if (isprintable == 1) {
        return (0);
    } else {
        return (1);
    }
}
