/*
** EPITECH PROJECT, 2018
** my_strncpy.c
** File description:
** Copy n characters from a string into another
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int letter;

    n -= 1;
    for (letter = 0; letter <= n; letter++) {
        if (src[letter] == '\0') {
            dest[letter] = '\0';
            return (dest);
        }
        dest[letter] = src[letter];
    }
    return (dest);
}
