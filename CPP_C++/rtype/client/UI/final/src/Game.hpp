/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** ClientGame
*/

#pragma once

#include <thread>

#include "AScene.hpp"
#include "game/RType.hpp"
#include "PointerHandler.hpp"
#include "Event.hpp"
#include "RTypeNetworkInput.hpp"

class ClientGame : public AScene {
    public:
        ClientGame();
        ~ClientGame();

        void getEvents(game_t *, sf::RenderWindow *);
        void updateGame(game_t *, sf::RenderWindow *);
        void drawGame(game_t *, sf::RenderWindow *);

    protected:
    private:
        bool isRunning;
        //RType rt;
        sf::Texture t;
        sf::Sprite bg;
        RTypeNetworkInput inputs;
        std::vector<RTypeNetworkObject> outputs;
        std::map<size_t, std::unique_ptr<Drawable>> listObjects;

        std::thread threadUdp;

    private:
    
        const std::map<EnemyType, std::string> enemyName = {
            {EnemyType::EnemySentinel, "Sentinel"},
            {EnemyType::EnemySoldier, "Soldier"},
        };

        const std::map<MissileType, std::string> missileName = {
            {MissileType::MissileAlly, "AllyMissile"},
            {MissileType::MissileEnemy, "EnemyMissile"},
        };

        const std::map<uint32_t, sf::Color> playerColor = {
            {0, sf::Color::Blue},
            {1, sf::Color::Red},
            {2, sf::Color::Yellow},
            {3, sf::Color::Green},
        };

};
