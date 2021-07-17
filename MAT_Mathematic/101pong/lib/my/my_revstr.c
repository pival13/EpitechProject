/*
** EPITECH PROJECT, 2018
** my_revstr.c
** File description:
** Function that reverses a string.
*/

char *my_revstr(char *str)
{
    int n = 0;
    char stock;
    int i;

    for (i = 0; str[i] != '\0'; i++) {
    }
    for (i = i - 1; i > n; i--) {
        stock = str[i];
        str[i] = str[n];
        str[n] = stock;
        n++;
    }
    return (str);
}
