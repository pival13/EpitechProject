/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** jsonChecker
*/

#include "json.h"

static bool check_special_string(const char *s, size_t *idx)
{
    size_t i = *idx;
    if (s[i] == '"')
        do i += strcspn(s+i+1, "\"") + 1;
        while (s[i] == '"' && s[i-1] == '\\');
    if (s[i] != '"' && !strspn(s+*idx, "0123456789") &&
        strncasecmp(s+*idx, "true", 4) && strncasecmp(s+*idx, "false", 5) &&
        strncasecmp(s+*idx, "none", 4) && strncasecmp(s+*idx, "null", 4))
        return false;
    if (!strncasecmp(s+*idx, "true", 4) || !strncasecmp(s+*idx, "none", 4) ||
        !strncasecmp(s+*idx, "null", 4))
        i = *idx + 4 - 1;
    if (!strncasecmp(s+*idx, "false", 5))
        i = *idx + 5 - 1;
    if (strspn(s+*idx, "0123456789")) {
        i = *idx + strspn(s+*idx, "0123456789") - 1;
        if (s[i+1] == '.' && strspn(s+i+2, "0123456789"))
            i += strspn(s+i+2, "0123456789") + 1;
    }
    *idx = i;
    return true;
}

static bool check_special_char(const char *s, size_t i, char *type)
{
    if ((type[0] == 0 && strspn(s+i, ",:}]") > 0) ||
        (s[i] == ',' && strspn(s+i-1, "{[:,") > 0) ||
        (s[i] == ':' && (type[strlen(type)-1] != '{' || s[i-1] != '"')) ||
        (s[i] == '}' && (type[strlen(type)-1] != ':' || s[i-1] == ':') &&
            s[i-1] != '{') ||
        (s[i] == ']' && (type[strlen(type)-1] != '[')) ||
        (strlen(type) == 1000 && strspn(s+i, "{[:") > 0))
        return false;
    if ((s[i] == ',' || s[i] == '}') && type[strlen(type)-1] == ':')
        type[strlen(type)-1] = 0;
    if (s[i] == '}' || s[i] == ']')
        type[strlen(type)-1] = 0;
    if (s[i] == '{' || s[i] == '[' || s[i] == ':')
        type[strlen(type)] = s[i];
    return strspn(s+i, "{:},[]") > 0;
}

bool json_is_valid(const char *src)
{
    char *s = malloc(sizeof(char) * (strlen(src)+1));
    char type[1000] = {0};
    bool last_string = false;

    s = json_clean_str(strcpy(s, src));
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (!last_string && check_special_string(s, &i))
            last_string = true;
        else if (!check_special_char(s, i, type)) {
            free(s);
            return false;
        } else
            last_string = false;
    }
    free(s);
    return type[0] == 0;
}
