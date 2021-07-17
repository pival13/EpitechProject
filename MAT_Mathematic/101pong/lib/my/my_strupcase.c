/*
** EPITECH PROJECT, 2018
** my_strupcase.c
** File description:
** Function that brings the lowercase letters
** to uppercase letters.
*/

char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 97 && str[i] <= 122)
            str[i] = str[i] - 32;
    }
    return (str);
}
