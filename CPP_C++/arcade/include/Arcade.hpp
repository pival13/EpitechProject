/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Arcade
*/

#pragma once

#include <memory>
#include <chrono>
#include <thread>
#include "ArcadeEvent.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "../src/lib/DLLoader.hpp"
#include "../src/lib/DirReader.hpp"

class Arcade {
    public:
        Arcade(const std::string &graph, const std::string &game) noexcept(false);
        ~Arcade();

        void play();

    private:
        void checkInput();
        void loadGame(const std::string &gamePath) noexcept(false);
        void loadGraph(const std::string &graphPath) noexcept(false);
        void changeGame();
        void changeGraph();

        ArcadeContent interface;
        DLLoader graphLib;
        DLLoader gameLib;
        std::unique_ptr<IDisplayModule> graph;
        std::unique_ptr<IGameModule> game;
        bool _isPowerUp;
        int _currentGraph;
};
