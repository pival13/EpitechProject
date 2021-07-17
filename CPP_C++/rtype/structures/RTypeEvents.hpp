/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RTypeEvents
*/

#pragma once

#include <chrono>

struct RTypeEvents
{
    enum EventType {
        GameTime,
        PlayerScore,
        ObjectCreate,
        ObjectCollid,
        ObjectDestroy
    } type;
    union {
        std::chrono::system_clock::time_point time;
        struct {
            int score;
            unsigned int playerNumber;
        } playerScore;
        size_t objectUuid;
    };
};
