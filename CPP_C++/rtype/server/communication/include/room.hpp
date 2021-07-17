/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** room
*/

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include "header.hpp"

/**
 * @brief Create a room.
 * 
 */
typedef struct create_room_s {
    header_t header;
    char name[Rtype::Size::nameLength];
    short place;
    short bomb;
    short life;
}create_room_t;

/**
 * @brief Get a room.
 * 
 */
typedef struct get_room_s {
    header_t header;
    char uuid[Rtype::Size::uuidLength];
    char name[Rtype::Size::nameLength];
    unsigned short port;
    short place;
    short numberOfPlayer;
    short bomb;
    short life;
}get_room_t;

/**
 * @brief Send by a client to join a room.
 * 
 */
typedef struct join_room_s {
    header_t header;
    char uuid[Rtype::Size::uuidLength];
}join_room_t;

/**
 * @brief Send by client to leave a room.
 * 
 */
typedef struct leave_room_t {
    header_t header;
    char uuid[Rtype::Size::uuidLength];
}leave_room_t;

typedef struct room_location_s {
    header_t header;
    char roomUuid[Rtype::Size::uuidLength];
    unsigned short port;
}room_loation_t;

#endif /* !ROOM_HPP_ */
