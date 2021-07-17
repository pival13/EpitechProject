/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Soldier
*/

#include "Soldier.hpp"
#include "game/RType.hpp"

Soldier::Soldier()
: Enemy(nullptr, EnemyType::EnemySoldier, {120*0.6, 72*0.6, 20}, 1, {
    {"Idle", {
        std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../../client/UI/final/img_src/AE1.png",
        Transform({0, 0, 0}, {108, 72, 0}, {0.5, 0.5, 0.5}, {0,0,0}, {-0.6, 0.6, 1}), {108+22, 0}, 12
    }},
    {"Shoot", {
        std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../../client/UI/final/img_src/AES.png",
        Transform({0, 0, 0}, {210, 142, 0}, {0.5, 0.5, 0.5}, {0,0,0}, {-0.6, 0.6, 1}), {210, 0}, 6
    }},
}), lastShoot(std::chrono::system_clock::now())
{
    playAnimation("Idle", true);
}

Soldier::~Soldier()
{
}

Vector3 Soldier::getCloserEnemyAngle(RType &rt)
{
    auto players = rt.getPlayers();
    if (players.size() == 0)
        return {0, 0, 0};
    Vector3 pos = players.front()->getTransform().getGlobalPosition();

    for (const auto &player : players)
        if ((player->getTransform().getGlobalPosition()-transform.getGlobalPosition()).magnitude() < (pos-transform.getGlobalPosition()).magnitude())
            pos = player->getTransform().getGlobalPosition();
    pos -= transform.getGlobalPosition();

    double angle = std::atan2(pos.y, pos.x)*180/M_PI;
    if (transform.getScale().x < 0) angle = 180 - angle;
    return {0, 0, angle};
}

void Soldier::update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater)
{
    if (std::chrono::system_clock::now() > lastShoot + std::chrono::seconds(1)) {
        //lastShoot = std::chrono::system_clock::now();
        lastShoot += std::chrono::seconds(1);//TODO
        try {
            playAnimation("Shoot");
            RTypeObject *m = (rt.*creater)(RTypeObjectType::ObjectMissile, "EnemyMissile", transform.getPosition(), getCloserEnemyAngle(rt), transform.getScale());
            m->setDirectionMove({rt.mapWidth/5*1.5, 0, 0});
        } catch (const std::exception &e) {
            std::cerr << "[Soldier] Failed to send a missile: " << e.what() << std::endl;
        }
    }
    Enemy::update(rt, colliders, destroyer, creater);
}

Enemy *createInstance() { return new Soldier(); }