/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Player
*/

#include "Player.hpp"
#include "game/RType.hpp"

//Player::Player(GameObject *parent, const Vector3 &size, const std::string &materialPath, const Vector2 &sizeM, const Vector2 &offsetM, double rotationM, const Vector2 &scaleM)
//: Player(parent, size, materialPath, Transform(offsetM, sizeM, {0.5,0.5,0.5}, {0,0,rotationM}, {scaleM.x,scaleM.y,1}))
//{}

Player::Player(GameObject *parent, const Vector3 &size, const std::map<std::string, AnimatedSpriteData> &animData)
: GameObject(Transform({0,0,0}, size), parent)
//, RTypeObject(parent)
, RoundObject(Vector3(), size, parent)
, AnimatedSprite(10, animData, parent)
, life(3)
, score(0)
{
}

Player::~Player()
{
}

void Player::catchPowerUp(PowerUpType )
{

}

size_t Player::beenCollided()
{
    //score *= 0.9
    ;
    return --life;
}

void Player::update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater)
{
    if (transform.getPosition().x <= rt.border && direction.x < 0)
        direction.x = 0;
    if (transform.getPosition().y <= rt.border && direction.y < 0)
        direction.y = 0;
    if (transform.getPosition().x >= rt.mapWidth + rt.border && direction.x > 0)
        direction.x = 0;
    if (transform.getPosition().y >= rt.mapHeight + rt.border && direction.y > 0)
        direction.y = 0;
    RTypeObject::update(rt, colliders, destroyer, creater);
}

RTypeNetworkObject Player::toNetworkObject() const
{
    Vector3 vect;
    RTypeNetworkObject obj = {};
    
    obj.type = RTypeObjectType::ObjectPlayer;

    vect = transform.getGlobalPosition();
    obj.posx = uint32_t(vect.x);
    obj.posy = uint32_t(vect.y);

    obj.angle = int32_t(transform.getGlobalDegRotation().z);

    vect = transform.getGlobalScale();
    obj.scalex = uint32_t(vect.x * 100);
    obj.scaley = uint32_t(vect.y * 100);

    obj.player.playerLife = life;
    obj.player.shield = false;//TODO
    return obj;
}
