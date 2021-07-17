/*
** EPITECH PROJECT, 2018
** my_strcat.c
** File description:
** Function that concatenates two strings.
*/

char *my_strstr(char *dest, char const *src)
{
    int j = 0;

    for (; dest[j] != 0; j++) {
    }
    for (int i = 0; src[i] != 0; i++) {
        dest[j] = src[i];
        j++;
    }
    return (dest);
}
