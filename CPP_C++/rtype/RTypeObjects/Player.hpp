/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Player
*/

#pragma once

#include "AnimatedSprite.hpp"
#include "RoundObject.hpp"
#include "RTypeObject.hpp"
#include "RTypeEnum.hpp"

class Player : public RTypeObject, public RoundObject, public AnimatedSprite {
    public:
        Player(GameObject *parent, const Vector3 &size, const std::map<std::string, AnimatedSpriteData> &animData);
        virtual ~Player();

        virtual int64_t getScore() const { return score; }
        virtual void earnPoint(int64_t point) { score += point; }
        virtual void catchPowerUp(PowerUpType powerUp);

        virtual size_t beenCollided();
        virtual void update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater);
        virtual void shoot() = 0;

        virtual RTypeNetworkObject toNetworkObject() const;

        virtual void move(const Vector3 &d) { Drawable::move(d); }
        virtual void scale(const Vector3 &d) { Drawable::scale(d); }
        virtual void rotate(const Vector3 &d) { Drawable::rotate(d); }

    protected:
        size_t life;
        int64_t score;
    private:
};
