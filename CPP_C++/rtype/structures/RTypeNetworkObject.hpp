/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RTypeNetworkObject
*/

#pragma once

#include <cstdint>
#include "RTypeEnum.hpp"

struct RTypeNetworkObject {
    uint64_t uuid;
    enum RTypeObjectType type:8;
    unsigned int posx:16;
    unsigned int posy:16;
    int angle:9;// degree, -180 - 180°
    int scalex:10;// percent, 500 max
    int scaley:10;// percent, 500 max
    union {
        struct {
            //char playerName[16];
            unsigned int playerLife:4;//Max 0b1111 -> 15
            unsigned int playerId:3;//Max 0b111 -> 7
            unsigned int shield:1;
        } player;
        struct {
            unsigned int enemyLife:8;
            EnemyType enemyType:8;
        } enemy;
        unsigned int obstacleLife:8;
        MissileType missileType:8;
        PowerUpType powerUpType:8;
    };
};
