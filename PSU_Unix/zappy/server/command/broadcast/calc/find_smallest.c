/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** find_smallest
*/

#include "server.h"

/**
* @brief Return the distance between two points.
*
* @param s_x Sender x position.
* @param s_y Sender y position.
* @param r_x Receiver x position.
* @param r_y Receiver y position.
* @return float
*/
float calc(int s_x, int s_y, int r_x, int r_y)
{
    double x = pow((r_x - s_x), 2);
    double y = pow((r_y - s_y), 2);

    return sqrt(x + y);
}

/**
* @brief Find the smallest x position which seperate receiver from sender.
*
* @param sender Player who is sending the message.
* @param receiver Player who will receive the message.
* @param width The width of the map.
* @return int
*/
int found_x(client_t sender, client_t receiver, int width)
{
    int x1 = receiver.x - sender.x;
    int x2 = receiver.x + width - sender.x;

    return abs(x1) < abs(x2) ? receiver.x : receiver.x + width;
}

/**
* @brief Find the smallest y position which seperate receiver from sender.
*
* @param sender Player who is sending the message.
* @param receiver Player who will receive the message.
* @param height The height of the map.
* @return int
*/
int found_y(client_t sender, client_t receiver, int height)
{
    int y1 = receiver.y - sender.y;
    int y2 = receiver.y + height - sender.y;

    return abs(y1) < abs(y2) ? receiver.y : receiver.y + height;
}