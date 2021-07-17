/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Obstacle
*/

#pragma once

#include "AnimatedSprite.hpp"
#include "SquareObject.hpp"
#include "RTypeObject.hpp"

class Obstacle : public RTypeObject, public SquareObject, public AnimatedSprite {
    public:
        Obstacle(GameObject *parent, const Vector3 &size, const std::map<std::string, AnimatedSpriteData> &animData);
        Obstacle(GameObject *parent, const Vector3 &size, size_t life, const std::map<std::string, AnimatedSpriteData> &animData);
        virtual ~Obstacle();

        virtual int64_t scoreOnDefeat() const { return 2; }

        virtual size_t beenCollided() { if (life == 0) return 1; return --life; };
        virtual void update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater);
        
        virtual RTypeNetworkObject toNetworkObject() const;

        virtual void move(const Vector3 &d) { Drawable::move(d); }
        virtual void scale(const Vector3 &d) { Drawable::scale(d); }
        virtual void rotate(const Vector3 &d) { Drawable::rotate(d); }

    protected:
        size_t life;
    private:
};
