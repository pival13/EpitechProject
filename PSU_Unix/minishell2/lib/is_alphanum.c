/*
** EPITECH PROJECT, 2018
** my_str_isalphanum.c
** File description:
** Return if the string is composed of number and letter.
*/

int is_alphanum(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if ((str[i] > '9' || str[i] < '0') && (str[i] > 'z' || str[i] < 'a') \
&& (str[i] > 'Z' || str[i] < 'A') && str[i] != '_')
            return (0);
    return (1);
}
