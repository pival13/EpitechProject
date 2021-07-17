/*
** EPITECH PROJECT, 2018
** my_strcmp
** File description:
** Compare the first letter of two string
*/

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    for (; s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'; i++);
    if (s1[i] == '\0' && s2[i] == '\0')
        return (0);
    else
        return (s1[i] - s2[i]);
}

int my_strcmp_begin(char const *s1, char const *s2_b)
{
    int i = 0;

    for (; s1[i] == s2_b[i] && s1[i] != '\0' && s2_b[i] != '\0'; i++);
    if (s2_b[i] == '\0')
        return (0);
    else
        return (s1[i] - s2_b[i]);
}
