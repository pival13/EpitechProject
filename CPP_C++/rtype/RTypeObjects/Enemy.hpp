/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Enemy
*/

#pragma once

#include "AnimatedSprite.hpp"
#include "RoundObject.hpp"
#include "RTypeObject.hpp"

class Enemy : public RTypeObject, public RoundObject, public AnimatedSprite {
    public:
        Enemy(GameObject *parent, EnemyType type, const Vector3 &size, size_t life, const std::map<std::string, AnimatedSpriteData> &animData);
        virtual ~Enemy();

        virtual int64_t scoreOnDefeat() const { return 10; }
        virtual size_t beenCollided() { return --life; }

        virtual void update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater);

        virtual RTypeNetworkObject toNetworkObject() const;

        virtual void move(const Vector3 &d) { Drawable::move(d); }
        virtual void scale(const Vector3 &d) { Drawable::scale(d); }
        virtual void rotate(const Vector3 &d) { Drawable::rotate(d); }

    protected:
        size_t life;
    
    private:
        EnemyType _type;
};
