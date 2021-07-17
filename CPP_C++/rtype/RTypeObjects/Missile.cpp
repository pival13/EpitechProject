/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Missile
*/

#include "Missile.hpp"
#include "game/RType.hpp"

Missile::Missile(GameObject *parent, MissileType t, const Vector3 &size, const std::string &materialPath, const Vector2 &sizeM, const Vector2 &offsetM, double rotationM, const Vector2 &scaleM)
: Missile(parent, t, size, materialPath, Transform(offsetM, sizeM, {0.5,0.5,0.5}, {0,0,rotationM}, {scaleM.x,scaleM.y,1}))
{}

Missile::Missile(GameObject *parent, MissileType _type, const Vector3 &size, const std::string &materialPath, const Transform &materialData)
: GameObject(Transform(Vector3(), size), parent)
//, RTypeObject(parent)
, RoundObject(Vector3(), size, parent)
, Drawable(materialPath, materialData)
, type(_type)
, holder(nullptr)
{
}

Missile::~Missile()
{
}

void Missile::update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater)
{
    if (!collider.onCollision)
        collider.onCollision = [this, &rt, &destroyer](Collider &c) {
            if (holder) {
                bool ok = false;
                for (const auto &e : rt.getPlayers())
                    if (e == holder)
                        ok = true;
                if (!ok)
                    holder = nullptr;
            }

            Player *p;
            Enemy *e;
            if (Obstacle *o = dynamic_cast<Obstacle*>(&c.gameObject)) {
                rt.addEvents(RTypeEvents::ObjectCollid, this);
                rt.addEvents(RTypeEvents::ObjectCollid, o);
                if (o->beenCollided() == 0) {
                    (rt.*destroyer)(o);
                    if (holder) holder->earnPoint(o->scoreOnDefeat());
                }
                if (beenCollided() == 0) return (rt.*destroyer)(this);
            } else if (type != MissileType::MissileAlly && (p = dynamic_cast<Player*>(&c.gameObject))) {
                rt.addEvents(RTypeEvents::ObjectCollid, this);
                rt.addEvents(RTypeEvents::ObjectCollid, p);
                if (p->beenCollided() == 0) {
                    (rt.*destroyer)(p);
                    //if (holder) holder->earnPoint(p->scoreOnDefeat());
                }
                if (beenCollided() == 0) return (rt.*destroyer)(this);
            } else if (type != MissileType::MissileEnemy && (e = dynamic_cast<Enemy*>(&c.gameObject))) {
                rt.addEvents(RTypeEvents::ObjectCollid, this);
                rt.addEvents(RTypeEvents::ObjectCollid, e);
                if (e->beenCollided() == 0) {
                    (rt.*destroyer)(e);
                    if (holder) holder->earnPoint(e->scoreOnDefeat());
                }
                if (beenCollided() == 0) return (rt.*destroyer)(this);
            } else if (Missile *m = dynamic_cast<Missile*>(&c.gameObject))
                if (m->type != type) {
                    rt.addEvents(RTypeEvents::ObjectCollid, this);
                    rt.addEvents(RTypeEvents::ObjectCollid, m);
                    if (m->beenCollided() == 0) (rt.*destroyer)(m);
                    if (beenCollided() == 0) return (rt.*destroyer)(this);
                }
        };
    RTypeObject::update(rt, colliders, destroyer, creater);
}

RTypeNetworkObject Missile::toNetworkObject() const
{
    Vector3 vect;
    RTypeNetworkObject obj = {};
    
    obj.type = RTypeObjectType::ObjectMissile;

    vect = transform.getGlobalPosition();
    obj.posx = uint32_t(vect.x);
    obj.posy = uint32_t(vect.y);

    vect = transform.getGlobalScale();
    obj.scalex = int32_t(vect.x * 100);
    obj.scaley = int32_t(vect.y * 100);

    obj.angle = int32_t(transform.getGlobalDegRotation().z);
    if (obj.scalex < 0) obj.angle = 360- obj.angle;
    obj.angle = ((obj.angle + 180) % 360 + 360) % 360 - 180;

    obj.missileType = type;
    return obj;
}
