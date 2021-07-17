/*
** EPITECH PROJECT, 2021
** AIA_gomoku
** File description:
** Brain
*/

#pragma once

#include "Gomoku.hpp"
#include "Defender.hpp"
#include "ThreatSpaceSearch.hpp"

class Brain {
public:
    Brain(size_t sizeX) : Brain(sizeX, sizeX) {}
    Brain(size_t sizeX, size_t sizeY);
    ~Brain() {}

    int run();

protected:
private:
    std::deque<Vector2> selectMostUse(const std::deque<Vector2> &poss);

    void initBoard();
    void makeAMove();
    void parseMessage(const std::string &s);    

private:
    GomokuBoard board;
    Defender defender;
    ThreatSpaceSearch tss;
    bool running = true;
    bool begin = false;
};
