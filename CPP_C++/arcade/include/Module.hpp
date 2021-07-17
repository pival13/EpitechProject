/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** AModule
*/

#pragma once

#include "ArcadeEvent.hpp"
#include <array>

class Module {
    public:
        Module(ArcadeContent &ac);
        ~Module();

    protected:
        ///Return the char at (x,y)
        ///Throw an exception if x or y is out of range
        ///Negative value return the char from the end instead of the beginning.
        char getMapAt(int x, int y) const noexcept(false);
        size_t getMapWidth() const;
        size_t getMapHeight() const;

        bool isKeyUp() const;
        bool isKeyRight() const;
        bool isKeyDown() const;
        bool isKeyLeft() const;
        bool isKeyEnter() const;
        bool isKeyBack() const;
        bool isKeyPressed() const;
        bool isKeyReleased() const;

        void moveUp(bool isReleased);
        void moveDown(bool isReleased);
        void moveRight(bool isReleased);
        void moveLeft(bool isReleased);
        void validate(bool isReleased);
        void cancel(bool isReleased);
        void backToMenu(bool isReleased);
        void restart(bool isReleased);
        void turnOff(bool isReleased);
        void nextGame(bool isReleased);
        void prevGame(bool isReleased);
        void nextGraph(bool isReleased);
        void prevGraph(bool isReleased);
        void releasePressedKey();
        void noEvent();

        void setGame(int game);
        void setGraph(int graph);
        int getGraph() const;

        void cleanMap();
        void setMapAt(int x, int y, char c) noexcept(false);

    private:
        void gameKey(ArcadeEvent::KeyValue key, bool isReleased);

        ArcadeContent &arcade;
};
