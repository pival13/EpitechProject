/*
** EPITECH PROJECT, 2019
** get_path
** File description:
** get the path from the env
*/

#include <stdlib.h>
#include "my.h"

int get_nb_words(char *str)
{
    int nb_words = 0;
    int new_word = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (new_word == 1 && str[i] != ':') {
            nb_words++;
            new_word = 0;
        }
        if (str[i] == ':')
            new_word = 1;
    }
    return (nb_words);
}

char **get_var_env(char **env, char *var)
{
    char **path;
    int str = 0;
    int j = 0;
    int k = 0;

    for (; env[str] && my_strncmp(env[str], var, my_strlen(var)) != 0; str++);
    if (!env[str])
        return (NULL);
    path = malloc(sizeof(char *) * (get_nb_words(env[str]) + 1));
    path[0] = string(&(env[str])[my_strlen(var)]);
    for (int i = 0; path[0][i] != '\0'; i++, k++)
        if (path[0][i] == ':') {
            path[j][k] = '\0';
            j++;
            k = -1;
            path[j] = &path[0][i+1];
        }
    path[j+1] = NULL;
    return (path);
}

char *get_home(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        if (my_strncmp(env[i], "HOME=", 5) == 0)
            return (&env[i][5]);
    return (NULL);
}

char *get_oldpwd(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        if (my_strncmp(env[i], "OLDPWD=", 7) == 0)
            return (&env[i][7]);
    return (NULL);
}
