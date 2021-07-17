/*
** EPITECH PROJECT, 2018
** my_putstr.c
** File description:
** Display the characters of a string.
*/

void my_putchar(char);

int my_putstr(char const *str)
{
    int n = 0;
    
    while (str[n] != '\0') {
        my_putchar(str[n]);
        n += 1;
    }    
}
