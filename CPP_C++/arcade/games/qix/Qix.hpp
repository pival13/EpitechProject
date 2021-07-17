/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Qix
*/

#ifndef QIX_HPP_
#define QIX_HPP_

#include "AGameModule.hpp"
#include <array>
#include <chrono>
#include <cmath>

typedef std::array<size_t, 2> pos_t;

class Qix : public AGameModule {
    public: enum Obj {
        PLAYER = '@',
        PLAYER_WALK = '$',
        QIX = '\\',
        STARK = '&',
        STARK_TAIL = '|',
        BORDER = '-',
        TRAIL = '^',
        BURN = '*',
        WALL = '#',
        GROUND = 0
    };

    public:
        Qix(ArcadeContent &ac);
        ~Qix();

        void update();

    private:
        bool isComplete();
        bool isWalkable(size_t x, size_t y, char obj);
        bool isNextCell(size_t x, size_t y, char cell, bool large=false) const;
        pos_t posNextCell(size_t x, size_t y, char cell, bool large=false) const;
        pos_t getQixPos() const;
        std::array<pos_t, 3> getEnemyPos() const;
        void refreshMap(char old, char newc);
        pos_t posCloserBorder(size_t x, size_t y) const;

        void initGame();
        void recreateWall();
        bool isNotWithQix(size_t x, size_t y);
        void drawGameOver();
        void gameOverPage();
        void gamePage();

        void gameOver();
        void burnTrail();
        void moveUnit();
        void moveQix(pos_t);
        void moveStark(std::array<pos_t, 2>);
        void moveEnemies();

        std::chrono::milliseconds enemyTimer;
        std::chrono::milliseconds unitTimer;
        pos_t beginWalk;
        int live = 3;
        int page = 0;
        int level = 0;
};

extern "C" Qix *getGameModule(ArcadeContent &ac);

#endif /* !QIX_HPP_ */
