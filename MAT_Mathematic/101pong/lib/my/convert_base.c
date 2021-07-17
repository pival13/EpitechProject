/*
** EPITECH PROJECT, 2018
** convert_base.c
** File description:
** Function that converts a string in another base string.
*/

#include <stdlib.h>

int errorfunc(char *nbr, int base)
{
    int error = 0;

    for (int i = 0; nbr[i] != '\0'; i++) {
        if (nbr[i] > '9')
            nbr[i] -= 7;
        if ((nbr[i] - 47) > base || nbr[i] == '-')
            error = 1;
        if (nbr[i] == '0' && nbr[i + 1] < 48)
            error = 2;
    }
    return (error);
}

int comprehension(char *nbr, int basefrom)
{
    int nbrfinal = 0;
    int digit = 1;
    int n = 0;
    int unit = 0;
    int negative = 0;

    for (n = 0; nbr[n] != '\0'; n++) {
        if (nbr[n] == '-')
            negative = 1;
    }
    for (n -= 1; n >= 0; n--) {
        if (nbr[n] >= '0' && nbr[n] <= '9')
            unit = (nbr[n] - 48) * digit;
        if (nbr[n] >= 'A' && nbr[n] <= 'F')
            unit = (nbr[n] - 65) * digit;
        nbrfinal += unit;
        digit *= basefrom;
    }
    return (nbrfinal);
}

char *convert(int nbr, int baseto, char *nbrfinal)
{
    int diviseur = baseto;
    int reste = 0;
    int n = (-1);
    char stock;

    for (int i = 0; nbr > 0; i++) {
        reste = nbr % diviseur;
        if (reste > 9)
            reste += 7;
        nbrfinal[i] = reste + 48;
        nbr = nbr / diviseur;
        n++;
    }
    for (int i = 0; i < n; i++) {
        stock = nbrfinal[i];
        nbrfinal[i] = nbrfinal[n];
        nbrfinal[n] = stock;
        n--;
    }
    return (nbrfinal);
}

char *mallocnbrfinal(int nbr, int baseto)
{
    int diviseur = baseto;
    int reste = 0;
    int n = 0;
    char *nbrfinal;

    for (int i = 0; nbr > 0; i++) {
        reste = nbr % diviseur;
        nbr -= reste;
        nbr = nbr / diviseur;
        n++;
    }
    nbrfinal = malloc(n);
    return (nbrfinal);
}

char *convert_base(char const *nbr, char const *base_from, char const *base_to)
{
    int error = 0;
    int basefrom = 0;
    int baseto = 0;
    char *nbrfinal;
    int number;

    for (int i = 0; base_from[i] != '\0'; i++) {
        basefrom++;
    }
    for (int i = 0; base_to[i] != '\0'; i++) {
        baseto++;
    }
    error = errorfunc(nbr, basefrom);
    if (error > 0) {
        return ("0");
    } else {
        number = comprehension(nbr, basefrom);
        nbrfinal = mallocnbrfinal(number, baseto);
        nbrfinal = convert(number, baseto, nbrfinal);
        return (nbrfinal);
    }
}
