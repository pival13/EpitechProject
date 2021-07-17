/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RTypeFactory
*/

#include "RTypeFactory.hpp"

std::map<std::string, DLLoader> RTypeFactory::_dlls;
std::map<std::string, DirReader> RTypeFactory::_dirs;

RTypeFactory::~RTypeFactory()
{
}

std::unique_ptr<Player> RTypeFactory::createPlayer(const std::string &kind)
{
    if (!_dlls.count("Player::" + kind) || !_dlls["Player::"+kind]) {
        std::string path(__FILE__);
        DLLoader dll(path.substr(0, path.find_last_of("/\\")) + "/player", kind);
        _dlls["Player::" + kind] = dll;
    }
    return std::unique_ptr<Player>(_dlls["Player::" + kind].getFunction<Player *()>("createInstance")());
}

std::unique_ptr<Enemy> RTypeFactory::createEnemy(const std::string &kind)
{
    if (!_dlls.count("Enemy::" + kind)) {
        std::string path(__FILE__);
        DLLoader dll(path.substr(0, path.find_last_of("/\\")) + "/enemy", kind);
        _dlls["Enemy::" + kind] = dll;
    }
    return std::unique_ptr<Enemy>(_dlls["Enemy::" + kind].getFunction<Enemy *()>("createInstance")());
}

std::unique_ptr<Enemy> RTypeFactory::createEnemyRandom()
{
    if (!_dirs.count("Enemy")) {
        if (_dirs.empty())
            srand(uint32_t(time(nullptr)));
        std::string path(__FILE__);
        DirReader dir(path.substr(0, path.find_last_of("/\\")) + "/enemy");
        _dirs["Enemy"] = dir;
    } else
        _dirs["Enemy"].refresh();
    #ifdef _WIN32
    auto list = _dirs["Enemy"].getFiles(R"(.*\\[^\\]+\.dll)");
    #else
    auto list = _dirs["Enemy"].getFiles(".*/lib[^/]+\\.so");
    #endif
    if (list.size() == 0) {
        std::vector<std::string> dll;
        for (const auto &p : _dlls) if (p.first.substr(0, 7) == "Enemy::") dll.push_back(p.first);
        if (dll.size() == 0)
            throw std::runtime_error("RTypeFactory::createEnemyRandom Impossible to create a single enemy.");
        return std::unique_ptr<Enemy>(_dlls[dll[rand() % dll.size()]].getFunction<Enemy *()>("createInstance")());
    }
    std::smatch m;
    #ifdef _WIN32
    std::regex_search(list[rand() % list.size()], m, std::regex(R"(\\([^\\]+)\.dll)"));
    #else
    std::regex_search(list[rand() % list.size()], m, std::regex(R"(/lib([^/]+)\.so)"));
    #endif
    return createEnemy(m[1].str());
}

std::unique_ptr<Missile> RTypeFactory::createMissile(const std::string &kind)
{
    if (!_dlls.count("Missile::" + kind)) {
        std::string path(__FILE__);
        DLLoader dll(path.substr(0, path.find_last_of("/\\")) + "/missile", kind);
        _dlls["Missile::" + kind] = dll;
    }
    return std::unique_ptr<Missile>(_dlls["Missile::" + kind].getFunction<Missile *()>("createInstance")());
}

std::unique_ptr<Obstacle> RTypeFactory::createObstacle(const std::string &kind)
{
    if (!_dlls.count("Obstacle::" + kind)) {
        std::string path(__FILE__);
        DLLoader dll(path.substr(0, path.find_last_of("/\\")) + "/obstacle", kind);
        _dlls["Obstacle::" + kind] = dll;
    }
    return std::unique_ptr<Obstacle>(_dlls["Obstacle::" + kind].getFunction<Obstacle *()>("createInstance")());
}

std::unique_ptr<Obstacle> RTypeFactory::createObstacleRandom()
{
    if (!_dirs.count("Obstacle")) {
        if (_dirs.empty())
            srand(uint32_t(time(nullptr)));
        std::string path(__FILE__);
        DirReader dir(path.substr(0, path.find_last_of("/\\")) + "/obstacle");
        _dirs["Obstacle"] = dir;
    } else
        _dirs["Obstacle"].refresh();
    #ifdef _WIN32
    auto list = _dirs["Obstacle"].getFiles(R"(.*\\.+\.dll)");
    #else
    auto list = _dirs["Obstacle"].getFiles(".*/lib.+\\.so");
    #endif
    if (list.size() == 0) {
        std::vector<std::string> dll;
        for (const auto &p : _dlls) if (p.first.substr(0, 7) == "Obstacle::") dll.push_back(p.first);
        if (dll.size() == 0)
            throw std::runtime_error("RTypeFactory::createObstacleRandom Impossible to create a single obstacle.");
        return std::unique_ptr<Obstacle>(_dlls[dll[rand() % dll.size()]].getFunction<Obstacle *()>("createInstance")());
    }
    std::smatch m;
    #ifdef _WIN32
    std::regex_search(list[rand() % list.size()], m, std::regex(R"(\\([^\\]+)\.dll)"));
    #else
    std::regex_search(list[rand() % list.size()], m, std::regex(R"(/lib([^/]+)\.so)"));
    #endif
    return createObstacle(m[1].str());
}

std::unique_ptr<PowerUp> RTypeFactory::createPowerUp(const std::string &kind)
{
    if (!_dlls.count("PowerUp::" + kind)) {
        std::string path(__FILE__);
        DLLoader dll(path.substr(0, path.find_last_of("/\\")) + "/powerup", kind);
        _dlls["PowerUp::" + kind] = dll;
    }
    return std::unique_ptr<PowerUp>(_dlls["PowerUp::" + kind].getFunction<PowerUp *()>("createInstance")());
}