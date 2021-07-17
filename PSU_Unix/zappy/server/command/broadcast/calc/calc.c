/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** calc
*/

#include "server.h"

/**
* @brief Return the direction from where the message has been send.
*
* @param cord_y The smallest x.
* @param cord_x The samllest y.
* @return short
*/
static short direction_broadcast(int cord_y, int cord_x)
{
    switch (cord_y) {
    case 0:
        switch (cord_x) {
        case 0: return 0;
        case 1: return 7;
        default: return 3;
        }
    case 1:
        switch (cord_x) {
        case 0: return 5;
        case 1: return 6;
        default: return 4;
        }
    default:
        switch (cord_x) {
        case 0: return 1;
        case 1: return 8;
        default: return 2;
        }
    }
}

/**
* @brief Save the new smallest postion.
*
* @param ret Float array.
* @param i Y of the smallest direction.
* @param j X of the smallest direction.
* @param result The new smallest distance between sender and receiver.
* @return float *
*/
static float *atr(float ret[3], int i, int j, float result)
{
    ret[0] = j;
    ret[1] = i;
    ret[2] = result;
    return ret;
}

/**
* @brief Find the smallest direction to send the message.
* @return float *
*/
static float *calc_dir_without_orientation(client_t *sender, int receivey, \
int receivex)
{
    int array[3] = {0, 1, -1};
    float result = 0;
    float *ret = malloc(sizeof(float) * 3);

    ret[0] = 0.f;
    ret[1] = 0.f;
    ret[2] = calc(sender->x, sender->y, receivex, receivey);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result = calc(sender->x, sender->y, receivey + array[i], \
receivex + array[j]);
            result < ret[2] ? ret = atr(ret, array[i], array[j], result) : 0;
        }
    }
    return ret;
}

/**
* @brief Return the direction depending of the receiver direction.
*
* @param receiver Player who receive the message.
* @param dir Current direction which irrespective the receiver direction.
* @return short
*/
short calc_dir_with_orientation(client_t *receiver, short dir)
{
    short value = 0;

    if (dir == 0) return 0;
    switch (receiver->direc) {
    case UP:
        value = 0;
        break;
    case RIGHT:
        value = 2;
        break;
    case DOWN:
        value = 4;
        break;
    default:
        value = 6;
        break;
    }
    if (dir + value <= 8)
        return dir + value;
    dir += value;
    return dir - 8;
}

/**
* @brief Find the smallest direction to send the message to the receiver.
*
* @param server Contains all informations about the current game.
* @param sender Player who is sending the message.
* @param receiver Player who will receive the message.
* @return short
*/
short calc_direction(server_t *server, client_t *sender, client_t *receiver)
{
    short dir = 0;
    float *save = calc_dir_without_orientation(sender, found_x(*sender, \
*receiver, server->args.width), found_y(*sender, *receiver, \
server->args.height));

    if (sender == receiver) {
        free(save);
        return 0;
    }
    dir = direction_broadcast(save[0], save[1]);
    free(save);
    return calc_dir_with_orientation(receiver, dir);
}
