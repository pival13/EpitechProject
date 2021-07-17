/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** ADisplayModule
*/

#pragma once

#include "IDisplayModule.hpp"
#include "Module.hpp"
#include "ParserArcadeFileTexture.hpp"

class ADisplayModule : public IDisplayModule, private Module {
    public:
        ADisplayModule(ArcadeContent &arcade);
        ~ADisplayModule() = default;

        virtual void setTexture(const std::string &fileName) = 0;
        virtual void updateEvent() = 0;
        virtual void display() = 0;

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

        void moveUp(bool isReleased=false);
        void moveDown(bool isReleased=false);
        void moveRight(bool isReleased=false);
        void moveLeft(bool isReleased=false);
        void validate(bool isReleased=false);
        void cancel(bool isReleased=false);
        void backToMenu(bool isReleased=false);
        void restart(bool isReleased=false);
        void turnOff(bool isReleased=false);
        void nextGame(bool isReleased=false);
        void prevGame(bool isReleased=false);
        void nextGraph(bool isReleased=false);
        void prevGraph(bool isReleased=false);
        void releasePressedKey();
        void noEvent();
};
