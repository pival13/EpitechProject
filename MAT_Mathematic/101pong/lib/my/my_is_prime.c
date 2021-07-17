/*
** EPITECH PROJECT, 2018
** my_is_prime.c
** File description:
** Function that returns 1 if the
** number is prime and 0 if it's not.
*/

int my_is_prime(int nb)
{
    int diviseur = 2;
    int trouve = 0;

    while (diviseur < nb && trouve == 0) {
        if ((nb % diviseur) == 0 && diviseur != nb) {
            trouve = 1;
            return (0);
        }
        diviseur = diviseur + 1;
    }
    if (trouve == 0)
        return (1);
    if (nb <= 1)
        return (0);
}
