/*
** EPITECH PROJECT, 2018
** my_strncpy.c
** File description:
** Functon that copies n characters in another string.
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int desti;

    for (int i = 0; i <= n || desti != 1; i++) {
        if (dest[i] == '\0')
            desti = 1;
        if (i > n) {
            dest[i] = '\0';
        } else {
            dest[i] = src[i];
        }
    }
    return (dest);
}
