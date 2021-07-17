/*
** EPITECH PROJECT, 2018
** my_strislower.c
** File description:
** Function that verify if only lowercase.
*/

int my_str_islower(char const *str)
{
    int islower = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] > 'z' || str[i] < 'a')
            islower = 1;
    }
    if (islower == 1) {
        return (0);
    } else {
        return (1);
    }
}
