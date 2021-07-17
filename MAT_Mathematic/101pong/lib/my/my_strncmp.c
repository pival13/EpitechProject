/*
** EPITECH PROJECT, 2018
** my_strncmp.c
** File description:
** Function that compares two strings.
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int	totaldifference = 0;
    int	s1end = 0;
    int	s2end = 0;
    int	valeurs1;
    int	valeurs2;

    for (int i = 0; i < n; i++) {
        valeurs1 = s1[i];
        valeurs2 = s2[i];

        totaldifference += (valeurs1 - valeurs2);
    }
    return (totaldifference);
}
