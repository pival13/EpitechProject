/*
** EPITECH PROJECT, 2018
** my_compute_square_root.c
** File description:
** Funciton that returns the square
** root of the number given as argument.
*/

int my_compute_square_root(int nb)
{
    int nbBase = nb;
    int nbfinal;
    float nbMult = 0.000000000000;
    int n = 1;

    while ((nbMult * nbMult) != nb && n != 999999999){
        nbMult = nb / n;
        n = n + 1;
    }
    nbfinal = nbMult;
    if ((nbfinal * nbfinal) != nbBase) {
        return (0);
    } else {
        return (nbfinal);
    }
}
