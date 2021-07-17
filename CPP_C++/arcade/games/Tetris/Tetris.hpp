/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Tetris
*/

#pragma once

#include "AGameModule.hpp"
#include "../../src/lib/DirReader.hpp"
#include <fstream>
#include <chrono>
#include <cstdlib>

typedef std::array<ssize_t, 2> spos_t;
typedef std::array<size_t, 2> pos_t;
typedef std::chrono::milliseconds msec;

class Tetris : public AGameModule {
    public:
        Tetris(ArcadeContent &ac);
        ~Tetris();

        void update();

    private:
        bool isActivePiece(pos_t pos) const;
        bool isActivePiece(char c) const;
        bool isBlockPiece(pos_t pos) const;
        bool isBlockPiece(char c) const;
        bool canMove(spos_t dir) const;
        std::array<size_t, 4> getRect(std::vector<pos_t> poss) const;

        void addPiece();
        void movePiece(spos_t dir);
        void rotatePiece();
        void fixedPiece();

        void loadPiece(const std::string &file);
        void gamePage();
        void drawGameOver();
        void gameOverPage();
        void drawError();
        void errorPage();

        msec now;
        int page;
        int score = 0;
        msec deltaTime;
        msec lastDown;
        std::vector<std::vector<std::vector<char>>> _pieces;
};

extern "C" Tetris *getGameModule(ArcadeContent &ac);