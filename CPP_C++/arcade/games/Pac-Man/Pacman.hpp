/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Pacman
*/

#pragma once

#include "AGameModule.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

typedef std::array<size_t, 2> pos_t;
typedef std::chrono::milliseconds msec;

class Pacman : public AGameModule {
    public: enum Obj {
        PLAYER = '@',
        GHOST1 = 'a',
        GHOST2 = 'b',
        GHOST3 = 'c',
        GHOST4 = 'd',
        EAT_GHOST1 = 'A',
        EAT_GHOST2 = 'B',
        EAT_GHOST3 = 'C',
        EAT_GHOST4 = 'D',
        POINT = '.',
        SUPER_POINT = '*',
        GROUND = ' ',
        WALL = '#'    
    };

    public:
        Pacman(ArcadeContent &ac);
        ~Pacman();

        void update();

    private:
        void tryCrossMap(pos_t &newPos);
        bool isWalkableGhost(pos_t pos);
        bool isEatable(pos_t pos);
        bool isEnemy(pos_t pos);
        bool isComplete();
        pos_t getPos(char obj);
        void refreshMap(char old, char newc);

        void gameOver();
        void respawnGhost(pos_t);
        void updateMap();
        void moveUnit();
        void moveEnemies();
        void initGame(int map);
        void drawUnableToLaunch();
        void drawGameOver();

        void unableToLaunchPage();
        void gamePage();
        void gameOverPage();

        msec now;

        int direction;
        int life = 3;
        int map = 0;
        int page = 1;
        bool drawn = false;
        bool dead = false;
        pos_t mapSize;
        msec playerTimer;
        msec enemyTimer[4];
        msec superTimer;
        size_t score;
        std::array<char, 4> beforeGhost = {' ', ' ', ' ', ' '};
        pos_t beginGhost[4];
};

extern "C" Pacman *getGameModule(ArcadeContent &ac);