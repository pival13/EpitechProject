/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** PowerUp
*/

#include "PowerUp.hpp"
#include "game/RType.hpp"

PowerUp::PowerUp(GameObject *parent, PowerUpType t, const Vector3 &size, const std::string &materialPath, const Vector2 &sizeM, const Vector2 &offsetM, double rotationM, const Vector2 &scaleM)
: PowerUp(parent, t, size, materialPath, Transform(offsetM, sizeM, {0.5,0.5,0.5}, {0,0,rotationM}, {scaleM.x,scaleM.y,1}))
{}

PowerUp::PowerUp(GameObject *parent, PowerUpType _type, const Vector3 &size, const std::string &materialPath, const Transform &materialData)
: GameObject(Transform({0,0,0}, size), parent)
//, RTypeObject(parent)
, RoundObject(Vector3(), size, parent)
, Drawable(materialPath, materialData)
, type(_type)
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater)
{
    if (!collider.onCollision)
        collider.onCollision = [this, &rt, &destroyer](Collider &c) {
            if (Player *p = dynamic_cast<Player*>(&c.gameObject)) {
                rt.addEvents(RTypeEvents::ObjectCollid, this);
                p->catchPowerUp(beenCollided());
                return (rt.*destroyer)(this);
            }
        };
    RTypeObject::update(rt, colliders, destroyer, creater);
}

RTypeNetworkObject PowerUp::toNetworkObject() const
{
    Vector3 vect;
    RTypeNetworkObject obj = {};
    
    obj.type = RTypeObjectType::ObjectPowerUp;

    vect = transform.getGlobalPosition();
    obj.posx = uint32_t(vect.x);
    obj.posy = uint32_t(vect.y);

    obj.angle = int32_t(transform.getGlobalDegRotation().z);

    vect = transform.getGlobalScale();
    obj.scalex = uint32_t(vect.x * 100);
    obj.scaley = uint32_t(vect.y * 100);

    obj.powerUpType = type;
    return obj;
}
