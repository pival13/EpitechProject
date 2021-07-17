/*
** EPITECH PROJECT, 2018
** my_put_nbr.c
** File description:
** Display number
*/

void my_putchar(char);

int my_put_nbr(int nb)
{
    long long m = 1;

    (nb < 0) ? (my_putchar('-'), nb *= -1) : (nb);
    for (m = 1; m <= nb/10; m *= 10);
    for (; m > 1; m /= 10) {
        my_putchar(nb/m + 48);
        nb %= m;
    }
    my_putchar(nb + 48);
    return (0);
}
