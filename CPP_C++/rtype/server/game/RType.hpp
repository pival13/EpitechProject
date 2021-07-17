/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RType
*/

#pragma once

#include <chrono>
#include <thread>
#include <mutex>
#include <list>
#include <set>
#include <map>

#include "Game.hpp"
#include "RTypeFactory.hpp"
#include "RTypeNetworkObject.hpp"
#include "RTypeNetworkInput.hpp"
#include "RTypeEvents.hpp"

class RType : public Game {
    public:
        RType(const std::string &playerId);
        ~RType();

        void receiveInputs(const std::string &id, const std::vector<uint8_t> &data);
        std::vector<uint8_t> exportOutputs() const;

        void addEvents(const RTypeEvents &event) { events.push_back(event); }
        void addEvents(RTypeEvents::EventType type, const RTypeObject *obj);
        std::list<RTypeEvents> getEvents() const;

        size_t objectToUuid(const RTypeObject *obj);

        bool addPlayer(const std::string &playerId);

        RTypeObject *instantiate(const std::string &what, const Vector3 &pos, const Vector3 &rotation={0,0,0}, const Vector3 &scale={1,1,1});
        RTypeObject *instantiate(RTypeObjectType type, const std::string &what, const Vector3 &pos, const Vector3 &rotation={0,0,0}, const Vector3 &scale={1,1,1});
        void destroy(const RTypeObject *obj) { toDestroy.insert(obj); }

        std::list<RTypeObject *> getPlayers() const;

    private:
        void mainLoop();
        void instantiateRandomEnemy();
        void instantiateRandomObstacle();
        void destroy();

    public:
        static const double mapWidth;
        static const double mapHeight;
        static const double border;
        static const size_t maxPlayer;

        std::chrono::milliseconds deltaTime;

    private:
        size_t _uuid = 0;
        GameObject basicGO;
        std::map<std::string, size_t> players;
        std::map<size_t, std::unique_ptr<RTypeObject>> elements;
        std::list<Collider *> _colliders;
        std::set<const void*> toDestroy;

        std::list<RTypeEvents> events;

        bool over = false;
        std::mutex mutex;
        std::thread loopThread;

        std::chrono::system_clock::time_point lastLoopExecution;
        std::chrono::milliseconds enemySpam;
        std::chrono::system_clock::time_point lastNewEnemy;
        std::chrono::milliseconds obstacleSpam;
        std::chrono::system_clock::time_point lastNewObstacle;
};
/*

border                                                (mapWidth+2*border,mapHeight+2*border)
+---+-------------------------------------------------+
|                                                     | border
|   +---------------------------------------------+   +
|   |                  mapWidth                   |   |
|   |                                             |   |
|   |                                             |   |
|   |                                             |   |
|   |                                   mapHeight |   |
|   |                                             |   |
|   |                                             |   |
|   |                                             |   |
|   |                                             |   |
|   +---------------------------------------------+   +
|                                                     | border
+-------------------------------------------------+---+
(0,0)                                             border
*/


/*
    RType load dll avec emplacement particulier
    Appelle fonctoin propre dll

    Player -> Transform, HP, CurrentBoost
    PowerUp -> Transform
               catch(player)
    Missile -> Transform, Durée vie, HP
    Obstacle -> HP, Transform, PowerUp
    Enemy -> HP, Transform, PowerUp
             move(this, RType*::instantiate, map)
             attack(this, RType*::instantiate, map)
    
*/