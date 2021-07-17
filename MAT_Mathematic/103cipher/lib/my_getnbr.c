/*
** EPITECH PROJECT, 2018
** my_getnbr.c
** File description:
** Convert a str number into an int
*/

int my_getnbr(char const *str)
{
    int n = 0;
    int neg = 0;
    int nb = 0;

    while (str[n] == '-' || str[n] == '+') {
        if (str[n] == '-') {
            neg += 1;
        }
        n += 1;
    }
    while (str[n] <= '9' && str[n] >= '0') {
        nb = nb * 10 + (str[n] - 48);
        n += 1;
    }
    if (neg % 2 == 1) {
        nb *= -1;
    }
    return (nb);
}
