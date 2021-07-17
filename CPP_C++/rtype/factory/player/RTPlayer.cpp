/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RTPlayer
*/

#include "RTPlayer.hpp"
#include "game/RType.hpp"

RTPlayer::RTPlayer()
: Player(nullptr, {330/3, 170/2, 0}, {
    {"Idle", {
        std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../../client/UI/final/img_src/player.png",
        Transform({0, 0, 0}, {164, 327, 0}, {0.5, 0.5, 0.5}, {0, 0, 90}, {0.5, 0.5, 1}), {164+41, 0}, 14
    }}
}), lastShoot(std::chrono::system_clock::now())
, shootCadence(1000/2)
{
    collider.getTransform().setPosition({330/12, 0, 0});
    playAnimation("Idle", true);
    life = 3;
}

RTPlayer::~RTPlayer()
{
}

size_t RTPlayer::beenCollided()
{
    return --life;
}

void RTPlayer::update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater)
{
    if (_shoot && lastShoot + shootCadence <= std::chrono::system_clock::now()) {
        try {
            RTypeObject *m = (rt.*creater)(RTypeObjectType::ObjectMissile, "AllyMissile", transform.getPosition(), transform.getDegRotation(), transform.getScale());
            m->setDirectionMove({rt.mapWidth/5*1.5, 0, 0});
        } catch (const std::exception &e) {
            std::cerr << "[RTPlayer] Failed to send a missile: " << e.what() << std::endl;
        }
        lastShoot = std::chrono::system_clock::now();
    }
    _shoot = false;
    Player::update(rt, colliders, destroyer, creater);
}

void RTPlayer::shoot()
{
    _shoot = true;
}

Player *createInstance() { return new RTPlayer(); }