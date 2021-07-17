/*
** EPITECH PROJECT, 2018
** my_strcmp
** File description:
** Compare to string
*/

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    for (; (s1[i] == s2[i] || s1[i] == s2[i]+32 || s1[i] == s2[i]-32) && \
s1[i] != '\0'; i++);
    if (s1[i] == '\0' && s2[i] == '\0')
        return (0);
    else {
        if (s1[i] >= 'A' && s1[i] <= 'Z' && s2[i] >= 'a' && s2[i] <= 'z')
            return (s1[i] + 32 - s2[i]);
        else if (s1[i] >= 'a' && s1[i] <= 'z' && s2[i] >= 'A' && s2[i] <= 'Z')
            return (s1[i] - 32 - s2[i]);
        else
            return (s1[i] - s2[i]);
    }
}
