/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "header.hpp"

typedef struct player_uuid_s
{
    header_t header;
    char uuid[Rtype::Size::uuidLength];
}player_uuid_t;

#endif /* !PLAYER_HPP_ */
