/*
** EPITECH PROJECT, 2019
** is_word
** File description:
** find if a word is in a sentance
*/

#include <stdlib.h>

int is_word(char *str, char *word)
{
    int j = 0;

    if (str == NULL || word == NULL) return (0);
    for (int i = 0; str[i] != '\0'; i++) {
        for (; word[j] != '\0' && str[i+j] == word[j]; j++);
        if (word[j] == '\0' && (str[i+j] == '-' || str[i+j] == '\0'))
            return (1);
        else
            j = 0;
        for (; str[i] != '-' && str[i+1] != '\0'; i++);
    }
    return (0);
}
