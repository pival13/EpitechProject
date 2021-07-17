/*
** EPITECH PROJECT, 2019
** verify
** File description:
** words
*/

#include "my.h"

int my_strcmp_n(char *str, char *str2, int j)
{
    if (str == NULL || str2 == NULL)
        return 0;
    for (int i = 0; i != my_strlen(str); i++, j++)
        if (str[i] != str2[j])
            return 0;
    return 1;
}

char *cpy_label(char *str)
{
    char *save = NULL;
    int j = 0;

    for (j = 0; str[j] != '\0' && str[j] != '\n' && str[j] != ' ' && str[j] \
!= '\t' && str[j] != LABEL_CHAR; j++);
    save = malloc(sizeof(char) * (j + 1));
    if (save == NULL)
        return (NULL);
    for (j = 0; str[j] != '\0' && str[j] != '\n' && str[j] != ' ' && str[j] \
!= '\t' && str[j] != LABEL_CHAR; j++) {
        save[j] = str[j];
    }
    save[j] = '\0';
    return save;
}

char *cpy_com(char *str)
{
    char *save = NULL;
    int j = 0;
    int k = 0;

    for (j = 0; str[j] != '\0' && str[j] != '\n' && str[j] != ' ' && str[j] \
!= LABEL_CHAR; j++);
    j++;
    for (k = j; str[k] != '\0' && str[k] != '\n' && str[k] != ' '; k++);
    save = malloc(sizeof(char) * (k+1));
        if (save == NULL)
            return (NULL);
    for (k = 0; str[j] != '\0' && str[j] != '\n' && str[j] != ' '; j++, k++)
        save[k] = str[j];
    save[k] = '\0';
    return save;
}

int verify_word(char *str)
{
    for (int i = 0; str[i] != '\0' && str[i] != '\n' && str[i] != ' '; i++)
        if (str[i] == LABEL_CHAR)
            return 1;
    return 0;
}