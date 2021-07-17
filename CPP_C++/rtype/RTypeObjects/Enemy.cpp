/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Enemy
*/

#include "Enemy.hpp"
#include "RTypeFactory.hpp"
#include "game/RType.hpp"

Enemy::Enemy(GameObject *parent, EnemyType type, const Vector3 &size, size_t _life, const std::map<std::string, AnimatedSpriteData> &animData)
: GameObject(Transform(Vector3(), size), parent)
, RoundObject(Vector3(), size, parent)
, AnimatedSprite(10, animData, parent)
, life(_life)
, _type(type)
{
}

Enemy::~Enemy()
{
}

void Enemy::update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater)
{
    if (!collider.onCollision)
        collider.onCollision = [this, &rt, &destroyer](Collider &other) {
            Missile *m = nullptr;
            if (Player *p = dynamic_cast<Player*>(&other.gameObject)) {
                rt.addEvents(RTypeEvents::ObjectCollid, this);
                rt.addEvents(RTypeEvents::ObjectCollid, p);
                if (p->beenCollided() == 0) (rt.*destroyer)(p);
                if (beenCollided() == 0) return (rt.*destroyer)(this);
            } else if (Obstacle *o = dynamic_cast<Obstacle*>(&other.gameObject)) {
                rt.addEvents(RTypeEvents::ObjectCollid, this);
                rt.addEvents(RTypeEvents::ObjectCollid, o);
                if (o->beenCollided() == 0) (rt.*destroyer)(o);
                if (beenCollided() == 0) return (rt.*destroyer)(this);
            } else if ((m = dynamic_cast<Missile*>(&other.gameObject)) && m->type != MissileType::MissileEnemy) {
                rt.addEvents(RTypeEvents::ObjectCollid, this);
                rt.addEvents(RTypeEvents::ObjectCollid, m);
                if (m->beenCollided() == 0) (rt.*destroyer)(m);
                if (beenCollided() == 0) return (rt.*destroyer)(this);
            }
        };
    RTypeObject::update(rt, colliders, destroyer, creater);
}

RTypeNetworkObject Enemy::toNetworkObject() const
{
    Vector3 vect;
    RTypeNetworkObject obj = {};
    
    obj.type = RTypeObjectType::ObjectEnemy;

    vect = transform.getGlobalPosition();
    obj.posx = uint32_t(vect.x);
    obj.posy = uint32_t(vect.y);

    obj.angle = int32_t(transform.getGlobalDegRotation().z);

    vect = transform.getGlobalScale();
    obj.scalex = uint32_t(vect.x * 100);
    obj.scaley = uint32_t(vect.y * 100);

    obj.enemy.enemyLife = life;
    obj.enemy.enemyType = _type;
    return obj;
}
