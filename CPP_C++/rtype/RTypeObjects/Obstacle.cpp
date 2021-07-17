/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Obstacle
*/

#include "Obstacle.hpp"
#include "game/RType.hpp"

Obstacle::Obstacle(GameObject *parent, const Vector3 &size, const std::map<std::string, AnimatedSpriteData> &animData)
: Obstacle(parent, size, 0, animData) {}
Obstacle::Obstacle(GameObject *parent, const Vector3 &size, size_t _life, const std::map<std::string, AnimatedSpriteData> &animData)
: GameObject(Transform(Vector3(), size), parent)
, SquareObject(Vector3(), size, parent)
, AnimatedSprite(10, animData, parent)
, life(_life)
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater)
{
    if (!collider.onCollision)
        collider.onCollision = [this, &rt, &destroyer](Collider &c) {
            if (Player *p = dynamic_cast<Player*>(&c.gameObject)) {
                rt.addEvents(RTypeEvents::ObjectCollid, this);
                rt.addEvents(RTypeEvents::ObjectCollid, p);
                if (p->beenCollided() == 0) (rt.*destroyer)(p);
                if (beenCollided() == 0) return (rt.*destroyer)(this);
            } else if (Enemy *e = dynamic_cast<Enemy*>(&c.gameObject)) {
                rt.addEvents(RTypeEvents::ObjectCollid, this);
                rt.addEvents(RTypeEvents::ObjectCollid, e);
                if (e->beenCollided() == 0) (rt.*destroyer)(e);
                if (beenCollided() == 0) return (rt.*destroyer)(this);
            } else if (Missile *m = dynamic_cast<Missile*>(&c.gameObject)) {
                rt.addEvents(RTypeEvents::ObjectCollid, this);
                rt.addEvents(RTypeEvents::ObjectCollid, m);
                if (m->beenCollided() == 0) (rt.*destroyer)(m);
                if (beenCollided() == 0) return (rt.*destroyer)(this);
            }
        };
    RTypeObject::update(rt, colliders, destroyer, creater);
}

RTypeNetworkObject Obstacle::toNetworkObject() const
{
    Vector3 vect;
    RTypeNetworkObject obj = {};
    
    obj.type = RTypeObjectType::ObjectObstacle;

    vect = transform.getGlobalPosition();
    obj.posx = uint32_t(vect.x);
    obj.posy = uint32_t(vect.y);

    obj.angle = int32_t(transform.getGlobalDegRotation().z);

    vect = transform.getGlobalScale();
    obj.scalex = uint32_t(vect.x * 100);
    obj.scaley = uint32_t(vect.y * 100);

    obj.obstacleLife = life;
    return obj;
}
