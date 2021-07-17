/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** inventory
*/

#include "server.h"

/**
* @brief Merge two strings.
*
* @param str String to append.
* @param data String to merge.
*/
void append_data(char **str, char *data, char *name)
{
    my_strcat(str, name);
    my_strcat(str, " ");
    my_strcat(str, data);
    free(data);
}

/**
* @brief Append inventory's informations to client buffer part two.
*
* @param str String to append all informations.
* @param client Current client.
*/
void append_all_data_next(char **str, client_t *client)
{
    client->ressources.mendiane > 0 && strlen(*str) > 1 ? \
my_strcat(str, ", ") : 0;
    client->ressources.mendiane > 0 ? append_data(str, my_int_to_char\
(client->ressources.mendiane), "mendiane") : 0;
    client->ressources.phiras > 0 && strlen(*str) > 1 ? \
my_strcat(str, ", ") : 0;
    client->ressources.phiras > 0 ? append_data(str, my_int_to_char\
(client->ressources.phiras), "phiras") : 0;
    client->ressources.thystame > 0 && strlen(*str) > 1 ? \
my_strcat(str, ", ") : 0;
    client->ressources.thystame > 0 ? append_data(str, my_int_to_char\
(client->ressources.thystame), "thystame") : 0;
}

/**
* @brief Append inventory's informations to client buffer part one.
*
* @param str String to append all informations.
* @param client Current client.
*/
void append_all_data(char **str, client_t *client)
{
    if (client->food != 0)
        append_data(str, my_int_to_char(client->food), "food");
    client->ressources.linemate > 0 && strlen(*str) > 1 ? \
my_strcat(str, ", ") : 0;
    client->ressources.linemate > 0 ? append_data(str, my_int_to_char\
(client->ressources.linemate), "linemate") : 0;
    client->ressources.deraumere > 0 && strlen(*str) > 1 ? \
my_strcat(str, ", ") : 0;
    client->ressources.deraumere > 0 ? append_data(str, my_int_to_char\
(client->ressources.deraumere), "deraumere") : 0;
    client->ressources.sibur > 0 && strlen(*str) > 1 ? \
my_strcat(str, ", ") : 0;
    client->ressources.sibur > 0 ? append_data(str, my_int_to_char\
(client->ressources.sibur), "sibur") : 0;
    append_all_data_next(str, client);
}

/**
* @brief Check inventory.
*
* @param client Client who lauched the command.
*/
void inventory(client_t *client, __attribute__((unused)) server_t *server)
{
    char *str = NULL;

    my_strcat(&str, "[");
    append_all_data(&str, client);
    my_strcat(&str, "]\n");
    my_strcat(&client->buffer, str);
    free(str);
}
