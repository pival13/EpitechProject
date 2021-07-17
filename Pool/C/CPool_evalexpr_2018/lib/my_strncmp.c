/*
** EPITECH PROJECT, 2018
** my_strcmp
** File description:
** Compare the first letter of two string
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    for (i; s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i != n; i++);
    if (s1[i] == '\0' && s2[i] == '\0' || s1[i] == s2[i])
        return (0);
    else
        return (s1[i] - s2[i]);
}
