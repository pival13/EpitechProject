/*
** EPITECH PROJECT, 2018
** my_strlen.c
** File description:
** Display the longer of a string
*/

int my_strlen(char const *str)
{
    int	n = 0;

    while (str[n] != '\0') {
        n += 1;
    }
    return (n);
}
