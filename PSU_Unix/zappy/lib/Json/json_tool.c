/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonParser
*/

#include "json.h"

char *json_clean_str(char *s)
{
    bool is_string = false;
    size_t offset = 0;

    for (size_t i = 0; s[i+offset] != '\0'; i++) {
        while (!is_string && isspace(s[i+offset]))
            offset++;
        if (!is_string && i > 0 && s[i-1] == ',' && strspn(s+i+offset, "]}")) {
            i--;
            offset++;
        }
        if (s[i+offset] != '\0')
            s[i] = s[i+offset];
        else
            i--;
        if (s[i] == '\"' && (i == 0 || s[i-1] != '\\'))
            is_string = !is_string;
    }
    s[strlen(s)-offset] = 0;
    return s;
}

char *json_read_string(const char *s)
{
    char *str;
    size_t size = 0;

    while (s != NULL && *s != '\0' && *s != '\"')
        s++;
    if (s == NULL || *s == '\0' || strcspn(s+1, "\"") == strlen(s+1))
        return NULL;
    do
        size += strcspn(s+size+1, "\"") + 1;
    while (s[size-1] == '\\');
    str = (char *)malloc(sizeof(char) * size);
    str[size-1] = '\0';
    strncpy(str, s+1, size-1);
    return str;
}