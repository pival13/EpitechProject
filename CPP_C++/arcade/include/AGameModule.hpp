/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** AGameModule
*/

#pragma once

#include "IGameModule.hpp"
#include "Module.hpp"

class AGameModule : public IGameModule, private Module {
    public:
        AGameModule(ArcadeContent &arcade, const std::string &texturePath);
        ~AGameModule() = default;

        virtual void update() = 0;
        const std::string &getTextureFilepath() const;

    protected:
        ///Return the char at (x,y)
        ///Throw an exception if x or y is out of range
        ///Negative value return the char from the end instead of the beginning.
        char getMapAt(int x, int y) const noexcept(false);
        char getMapAt(const std::array<int, 2> &pos) const noexcept(false);
        char getMapAt(const std::array<size_t, 2> &pos) const noexcept(false);
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
        
        void setMapAt(int x, int y, char c) noexcept(false);
        void setMapAt(const std::array<int, 2> &pos, char c) noexcept(false);
        void setMapAt(const std::array<size_t, 2> &pos, char c) noexcept(false);
        void cleanMap();

        void backToMenu();

    private:
        const std::string _texturePath;
};