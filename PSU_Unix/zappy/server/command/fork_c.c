/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** fork_c
*/

#include "server.h"

/**
* @brief Create an egg object
*
* @param egg Egg about to be created.
* @param client Player who execute the command.
* @param freq Number actions in one second.
*/
static void create_egg(egg_t **egg, client_t *client, int freq)
{
    (*egg) = malloc(sizeof(egg_t));
    (*egg)->y = client->y;
    (*egg)->x = client->x;
    (*egg)->team_name = strdup(client->team_name);
    (*egg)->cooldown = 600.f / freq;
    (*egg)->id = max_in_team();
    (*egg)->id_parent = client->id;
    (*egg)->next = NULL;
}

/**
* @brief Add new egg to egg link list.
*
* @param egg Egg to add at the egg link list.
* @param egg_list Egg link list.
*/
static void add_egg_to_list(egg_t *egg, egg_t **egg_list)
{
    egg_t *base = NULL;

    if (*egg_list == NULL) {
        (*egg_list) = egg;
        return;
    }
    base = (*egg_list);
    for (; base && base->next != NULL; base = base->next);
    base->next = egg;
}

/**
* @brief Send egg informations to all graphical clients.
*
* @param server Contains all informations about the current game.
* @param egg Current egg.
* @param id Id of the current player.
*/
void send_egg_laid_informations(server_t *server, egg_t *egg, \
unsigned long int id)
{
    char *str = NULL;
    char *number = my_int_to_char(egg->id);

    my_strcat(&str, "enw ");
    my_strcat(&str, number);
    free(number);
    number = my_int_to_char(id);
    my_strcat(&str, " ");
    my_strcat(&str, number);
    free(number);
    number = my_int_to_char(egg->x);
    my_strcat(&str, " ");
    my_strcat(&str, number);
    free(number);
    number = my_int_to_char(egg->y);
    my_strcat(&str, " ");
    my_strcat(&str, number);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
    free(number);
}

/**
* @brief Create an egg.
*
* @param client Player who execute the command.
* @param server Contains all informations about the current game.
*/
void fork_c(client_t *client, server_t *server)
{
    egg_t *egg = NULL;

    create_egg(&egg, client, server->args.freq);
    add_egg_to_list(egg, &server->egg);
    my_strcat(&client->buffer, "ok\n");
    send_egg_laid_informations(server, egg, client->id);
}
