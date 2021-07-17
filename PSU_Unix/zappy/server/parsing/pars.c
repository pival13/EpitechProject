/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** pars
*/

#include "server.h"

int (*args_parser[])(int, char **, server_t *) = \
{port, port, width, width, height, height, name_x, name_x, \
clients_nb, clients_nb, freq, freq, basic_args};

const char *args[] = \
{"-p", "--port", \
"-x", "--width", \
"-y", "--height", \
"-n", "--nameX", \
"-c", "--clientsNb", \
"-f", "--freq", \
"-D", NULL};

/**
* @brief Init all the missing key to zero about the level path.
*
* @param server Contains all informations about the current game.
*/
static void init_level_json(server_t *server)
{
    json_t *json = json_get_with_key(server->json, "elevationPath");

    for (size_t i = 0; i != json_get_list_size(json); i++) {
        json_add_key(json_get_at_index(json, i), "linemate");
        json_add_key(json_get_at_index(json, i), "deraumere");
        json_add_key(json_get_at_index(json, i), "phiras");
        json_add_key(json_get_at_index(json, i), "mendiane");
        json_add_key(json_get_at_index(json, i), "thystame");
        json_add_key(json_get_at_index(json, i), "sibur");
    }
}

/**
* @brief Init the server structure.
*
* @param server Contains all informations about the current game.
* @return int
*/
static int init_server_struct(server_t *server)
{
    server->client = NULL;
    server->args.name = NULL;
    server->args.client_number = 0;
    server->args.freq = 100;
    server->args.height = 0;
    server->args.port = 0;
    server->args.width = 0;
    server->map = NULL;
    server->time.tv_sec = 0;
    server->time.tv_usec = 0;
    server->egg = NULL;
    server->refill_cooldown = 0;
    server->json = read_json_from_file(JSON_PATH);
    if (!server->json)
        return EXIT_FAILURE;
    init_level_json(server);
    return EXIT_SUCCESS;
}

/**
* @brief Fill args with basic settings
*
* @param i The position of the arguments in the array.
* @param arg Array of arguments.
* @param server Contains all information about the current game.
* @return int
*/
int basic_args(__attribute__((unused))int i, \
__attribute__((unused))char **av, server_t *server)
{
    json_t *json = json_get_with_key(server->json, "serverDefaultValues");
    size_t size = json_get_list_size(json_get_with_key(json, "name"));
    size_t index = 0;

    if (size == 0)
        return -1;
    pars_get_number(server, json);
    free_array(server->args.name);
    server->args.name = malloc(sizeof(char *) * (size + 1));
    for (; index < size; ++index) {
        server->args.name[index] = strdup(json_get_string(json_get_at_index\
(json_get_with_key(json, "name"), index)));
    }
    server->args.name[index] = NULL;
    return -2;
}

static int handle_args_next(server_t *server, char **av, int *i)
{
    for (int j = 0; args[j] != NULL; ++j) {
        my_strcmp(av[*i], (char *)args[j]) == 0 ? *i = args_parser[j]\
(*i, av, server) : 0;
        if (*i == -1)
            return EXIT_FAILURE;
        if (*i == -2)
            return EXIT_SUCCESS;
    }
    return 1;
}

/**
* @brief Launch parsing command.
*
* @param server Contains all informations about the current game.
* @param av Array of arguments.\

* @return int
*/
int handle_args(server_t *server, char **av)
{
    int n = 0;

    if (init_server_struct(server) == EXIT_FAILURE)
        return EXIT_FAILURE;
    for (int i = 1; av[i]; ++i) {
        n = handle_args_next(server, av, &i);
        if (n != 1)
            return n;
    }
    return EXIT_SUCCESS;
}
