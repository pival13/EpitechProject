/*
** EPITECH PROJECT, 2018
** my_strcmp.c
** File description:
** Function that compares two strings.
*/

int my_strcmp(char const *s1, char const *s2)
{
    int totaldifference = 0;
    int s1end = 0;
    int s2end = 0;
    int valeurs1;
    int valeurs2;

    for (int i = 0; s1end != 1 || s2end != 1; i++) {
        valeurs1 = s1[i];
        valeurs2 = s2[i];

        if (s1[i] == '\0')
            s1end = 1;
        if (s2[i] == '\0')
            s2end = 1;
        totaldifference += (valeurs1 - valeurs2);
    }
    return (totaldifference);
}
