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

    for (; str[n] == '-' || str[n] == '+'; n++)
        if (str[n] == '-')
            neg += 1;
    for (; str[n] <= '9' && str[n] >= '0'; n++)
        nb = nb * 10 + (str[n] - 48);
    if (neg % 2 == 1)
        nb *= -1;
    return (nb);
}
