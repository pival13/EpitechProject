/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RTypeEnum
*/

#pragma once

enum RTypeObjectType {
    ObjectPlayer,
    ObjectEnemy,
    ObjectObstacle,
    ObjectMissile,
    ObjectPowerUp
};

enum EnemyType {
    EnemySentinel,
    EnemySoldier
};

enum MissileType {
    MissileAlly,
    MissileEnemy
};

enum PowerUpType {
    PowerUpLife,
    PowerUpShield,
    PowerUpSpeed,
    PowerUpCadency,
    PowerUpFrontShot,
    PowerUpRearShot
};