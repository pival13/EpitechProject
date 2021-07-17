/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** name_x
*/

#include "server.h"

/**
* @brief Compare if a string is equal to another one in an array.
*
* @param args Array that we want to compare.
* @param arg String that we want to compare.
* @return an int 1 means equal, 0 otherwise.
*/
int compare(char **args, char *arg)
{
    for (int j = 0; args[j]; ++j)
        if (my_strcmp((char *)args[j], arg) == 0)
            return 1;
    return 0;
}

/**
* @brief Get different name given as argument.
*
* @param index The position of the arguments in the array.
* @param arg Array of arguments.
* @param server Contains all information about the current game.
* @return int
*/
int name_x(int index, char **arg, server_t *server)
{
    int new_index = index + 1;
    int i = 0;

    free_array(server->args.name);
    for (; arg[new_index]; ++new_index, ++i)
        if (compare((char **)args, arg[new_index]) == 1)
            break;
    if (i == 0)
        return -1;
    server->args.name = malloc(sizeof(char *) * (i + 1));
    i = 0;
    for (new_index = index + 1; arg[new_index]; ++new_index) {
        if (compare((char **)args, arg[new_index]) == 1)
            break;
        server->args.name[i] = strdup(arg[new_index]);
        ++i;
    }
    server->args.name[i] = NULL;
    new_index -= 1;
    return new_index;
}
