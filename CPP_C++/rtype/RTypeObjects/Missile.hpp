/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Missile
*/

#pragma once

#include "Drawable.hpp"
#include "RoundObject.hpp"
#include "RTypeObject.hpp"
#include "RTypeEnum.hpp"

class Player;

class Missile : public RTypeObject, public RoundObject, public Drawable {
    public:
        Missile(GameObject *parent, MissileType type, const Vector3 &size, const std::string &materialPath, const Vector2 &sizeInMaterial={-1,-1}, const Vector2 &offsetInMaterial={0,0}, double rotataionOfMaterial=0, const Vector2 &scaleOfMaterial={1,1});
        Missile(GameObject *parent, MissileType type, const Vector3 &size, const std::string &materialPath, const Transform &materialData);
        virtual ~Missile();

        void belongTo(Player *player) { holder = player; }
        virtual size_t beenCollided() { return 0; };
        virtual void update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater);

        virtual RTypeNetworkObject toNetworkObject() const;

        virtual void move(const Vector3 &d) { Drawable::move(d); }
        virtual void scale(const Vector3 &d) { Drawable::scale(d); }
        virtual void rotate(const Vector3 &d) { Drawable::rotate(d); }

    public:
        MissileType type;
    protected:
        std::string _hold = "";
        Player *holder;
};
