/*
** EPITECH PROJECT, 2019
** factoriel
** File description:
** factoriel de nb
*/

long long factoriel(int nb)
{
    long long nbr = 1;

    for (int i = 1; i <= nb; i++)
        nbr *= i;
    return (nbr);
}