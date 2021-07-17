/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** broadcast
*/

#include "server.h"

/**
 * @brief Return direction according with the direction of the receiver.
 *
 * @param dir_r Direction of the receiver.
 * @return int
 */
static int dir_sender_up(int dir_r)
{
    switch (dir_r) {
    case UP:
        return 5;
    case RIGHT:
        return 7;
    case DOWN:
        return 1;
    default:
        return 3;
    }
}

/**
 * @brief Return direction according with the direction of the receiver.
 *
 * @param dir_r Direction of the receiver.
 * @return int
 */
static int dir_sender_down(int dir_r)
{
    switch (dir_r) {
    case UP:
        return 1;
    case RIGHT:
        return 3;
    case DOWN:
        return 5;
    default:
        return 7;
    }
}

/**
 * @brief Return direction according with the direction of the receiver.
 *
 * @param dir_r Direction of the receiver.
 * @return int
 */
static int dir_sender_right(int dir_r)
{
    switch (dir_r) {
    case UP:
        return 3;
    case RIGHT:
        return 5;
    case DOWN:
        return 7;
    default:
        return 1;
    }
}

/**
 * @brief Return the direction which on the client has been ejected.
 *
 * @param dir_r Direction of the player who has been ejected.
 * @param dir Direction of the player who has ejected an another player.
 * @return int
 */
int dir_bc(int dir_r, int dir)
{
    switch (dir) {
    case UP:
        return dir_sender_up(dir_r);
    case DOWN:
        return dir_sender_down(dir_r);
    case RIGHT:
        return dir_sender_right(dir_r);
    default:
        switch (dir_r) {
        case UP:
            return 7;
        case RIGHT:
            return 1;
        case DOWN:
            return 3;
        default:
            return 5;
        }
    }
}

/**
 * @brief Send a message to the player who has been ejected.
 *
 * @param client Current client.
 * @param dir The directions of the ejection.
 */
void send_eject_bc(client_t *client, int dir)
{
    char *message = NULL;
    char *number = NULL;

    number = my_int_to_char(dir);
    my_strcat(&message, "eject: ");
    my_strcat(&message, number);
    my_strcat(&message, "\n");
    my_strcat(&client->buffer, message);
    free(message);
    free(number);
}
