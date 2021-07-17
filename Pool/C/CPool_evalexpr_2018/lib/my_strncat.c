/*
** EPITECH PROJECT, 2018
** my_strncat.c
** File description:
** Add the n first characters of the first sting to the end of the first one.
*/

char *my_strncat(char *dest, char const *src, int nb)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
        i++;
    while (src[j] != '\0' && j < nb) {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return (dest);
}
