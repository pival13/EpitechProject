/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** graphicals
*/

#include "server.h"

static void send_all_pnw(server_t *server)
{
    for (client_t *cli = server->client; cli; cli = cli->next) {
        if (!cli->graphic)
            send_new_client_to_graphical(server, cli);
    }
    for (egg_t *egg = server->egg; egg; egg = egg->next)
        send_egg_laid_informations(server, egg, egg->id_parent);
    for (egg_t *egg = server->egg; egg; egg = egg->next)
        if (egg->cooldown <= 0)
            send_egg_hacthing_graphical(server, egg->id);
}

/**
 * @brief Send to graphic login informations
 *
 * @param cli Current client.
 * @param server Contains all informations about the current game.
 */
void write_answer_for_graphic(client_t *cli, server_t *server)
{
    cli->graphic = true;
    msz(cli, server);
    sgt(cli, server);
    mct(cli, server);
    tna(cli, server);
    send_all_pnw(server);
}

/**
* @brief Add a number to the buffer.
*
* @param org_str String destination of num.
* @param num Number to transform in string.
*/
static void add_pos(char **org_str, int num)
{
    char *str = my_int_to_char(num);

    my_strcat(org_str, str);
    my_strcat(org_str, " ");
    free(str);
}

/**
* @brief Get the orientation for graphical object
*
* @param direc Direction of the current client.
* @return short
*/
static short get_orientation_for_graphical(short direc)
{
    switch (direc) {
    case UP:
        return 1;
    case RIGHT:
        return 2;
    case DOWN:
        return 3;
    default:
        return 4;
    }
}

/**
* @brief Send new client information to all graphical clients.
*
* @param server Contains all information about the current game.
* @param client Current client.
*/
void send_new_client_to_graphical(server_t *server, client_t *client)
{
    char *str = NULL;

    if (client->graphic || client->team_name == NULL)
        return;
    my_strcat(&str, "pnw ");
    add_pos(&str, client->id);
    add_pos(&str, client->x);
    add_pos(&str, client->y);
    add_pos(&str, get_orientation_for_graphical(client->direc));
    add_pos(&str, client->lvl);
    my_strcat(&str, client->team_name);
    my_strcat(&str, "\n");
    send_to_all_graphic(server->client, str);
    free(str);
}
