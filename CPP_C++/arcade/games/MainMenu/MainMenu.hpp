/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** MainMenu
*/

#pragma once

#include <iostream>
#include <array>
#include "AGameModule.hpp"
#include "../../src/lib/DirReader.hpp"

class MainMenu : public IGameModule, public Module {
    private:
        enum pagination {
            START,
            ENTER_NAME,
            LAUNCH
        };

    public:
        MainMenu(ArcadeContent &ac);
        ~MainMenu();

        const std::string &getTextureFilepath() const;
        void update();

    private:
        void startPage();
        void enterNickname();

        DirReader gameDirReader;
        DirReader graphDirReader;
        std::vector<std::string> gameDir;
        std::vector<std::string> graphDir;
        size_t page;
        size_t pos;
        size_t game;
        size_t graph;
        const std::string path = "games/MainMenu/texture.txt";
};

extern "C" MainMenu *getGameModule(ArcadeContent &);