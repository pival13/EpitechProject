/*
** EPITECH PROJECT, 2019
** my_pow
** File description:
** put an int at the power p
*/

int my_pow(int nb, int p)
{
    int nbr = 1;

    for (int i = 0; i < p; i++)
        nbr *= nb;
    return (nbr);
}
