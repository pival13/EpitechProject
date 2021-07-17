/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** *
*/

#pragma once

#include "GameObject.hpp"
#include "RTypeEnum.hpp"
#include "RTypeNetworkObject.hpp"

class RType;

class RTypeObject : virtual public GameObject {
    public:
        typedef void (RType::*RTypeDestroy)(const RTypeObject *);
        typedef RTypeObject *(RType::*RTypeCreate)(RTypeObjectType, const std::string &, const Vector3 &, const Vector3 &, const Vector3 &);

        //RTypeObject(GameObject *parent=nullptr);
        virtual ~RTypeObject();

        virtual RTypeNetworkObject toNetworkObject() const = 0;

        virtual void update(RType &game, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater);
        void setDirectionMove(const Vector3 &move) { direction = move; }

    protected:
        Vector3 direction = {0,0,0};
    
    public:
        using GameObject::onDestroy;
};
