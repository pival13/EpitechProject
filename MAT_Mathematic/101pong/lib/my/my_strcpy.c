/*
** EPITECH PROJECT, 2018
** my_strcpy.c
** File description:
** Function that copies a string into another.
*/

char *my_strcpy(char *dest, char const *src)
{
    int desti;
    int srci;

    for (int i = 0; desti != 1 || srci != 1; i++) {
        if (dest[i] == '\0')
            desti = 1;
        if (src[i] == '\0')
            srci = 1;
        dest[i] = src[i];
    }
    return (dest);
}
