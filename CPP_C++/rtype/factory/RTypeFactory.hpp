/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RTypeFactory
*/

#pragma once

#include <memory>
#include <map>

#include "DLLoader.hpp"
#include "DirReader.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"
#include "Obstacle.hpp"
#include "PowerUp.hpp"

class RTypeFactory {
    public:
        ~RTypeFactory();

        static std::unique_ptr<Player> createPlayer(const std::string &kind);
        static std::unique_ptr<Enemy> createEnemy(const std::string &kind);
        static std::unique_ptr<Enemy> createEnemyRandom();
        static std::unique_ptr<Missile> createMissile(const std::string &kind);
        static std::unique_ptr<Obstacle> createObstacle(const std::string &kind);
        static std::unique_ptr<Obstacle> createObstacleRandom();
        static std::unique_ptr<PowerUp> createPowerUp(const std::string &kind);

    private:
        static std::map<std::string, DLLoader> _dlls;
        static std::map<std::string, DirReader> _dirs;
};
