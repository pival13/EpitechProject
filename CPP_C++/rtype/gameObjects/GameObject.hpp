/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** GameObject
*/

#pragma once

#include "Transform.hpp"
#include <list>
#include <mutex>
#include <memory>
#include <functional>
#include <vector>

class Collider;

class GameObject {
    public:
        GameObject(GameObject *parent=nullptr);
        GameObject(const Transform &transform, GameObject *parent=nullptr);
        virtual ~GameObject();

        virtual void move(const Vector3 &dir);
        virtual void scale(const Vector3 &scale);
        virtual void rotate(const Vector3 &degAngle);
        Transform getTransform() const { return transform; }
        Transform &getTransform() { return transform; }
        void setParent(GameObject *parent, bool keepOnGlobal=true) { _parent = parent; transform.setParent(parent? &parent->transform: nullptr, keepOnGlobal); }
        GameObject *getParent() const { return _parent; }
        const std::list<Collider*> &getColliders() const { return _colliders; }

        void addCollider(Collider *collider) { if (collider != nullptr) _colliders.push_back(collider); }
        void removeCollider(Collider *collider);

        //static GameObject *instantiate(std::unique_ptr<GameObject> &&ptr, GameObject *parent=nullptr, const Vector3 &position={0,0,0}, const Vector3 &rotation={0,0,0}, const Vector3 &scale={1,1,1});
        //static void destroy(GameObject *ptr);

    protected:
        Transform transform;
        std::function<void()> onDestroy;

    private:
        GameObject *_parent;
        std::list<Collider *> _colliders;

        bool _isDestroy;
        //static std::mutex __mutex;
        //static std::list<std::unique_ptr<GameObject>> __gameObjects;
};
