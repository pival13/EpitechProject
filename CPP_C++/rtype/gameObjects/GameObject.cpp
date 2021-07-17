/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** GameObject
*/

#include "GameObject.hpp"
#include "Collider.hpp"
/*
std::mutex GameObject::__mutex;
std::list<std::unique_ptr<GameObject>> GameObject::__gameObjects;

GameObject *GameObject::instantiate(std::unique_ptr<GameObject> &&ptr, GameObject *parent, const Vector3 &position, const Vector3 &rotation, const Vector3 &scale)
{
    ptr->setParent(parent);
    ptr->transform.setPosition(position);
    ptr->transform.setDegRotation(rotation);
    ptr->transform.setScale(scale);
    GameObject *obj = ptr.release();
    __mutex.lock();
    __gameObjects.emplace_back(obj);
    __mutex.unlock();
    return obj;
}

void GameObject::destroy(GameObject *ptr)
{
    __mutex.lock();
    for (auto it = __gameObjects.begin(); it != __gameObjects.end(); ++it)
        if (it->get() == ptr) {
            __gameObjects.erase(it);
            break;
        }
    __mutex.unlock();
}
*/
GameObject::GameObject(GameObject *parent)
: transform(parent? &parent->transform: nullptr), onDestroy(nullptr), _parent(parent), _isDestroy(false)
{
}

GameObject::GameObject(const Transform &_transform, GameObject *parent)
: GameObject(parent) { transform = _transform; transform.setParent(parent? &parent->transform: nullptr, false); }

GameObject::~GameObject()
{
    _isDestroy = true;
    if (onDestroy)
        onDestroy();
}

void GameObject::move(const Vector3 &move)
{
    transform.setPosition(transform.getPosition() + move.rotate(transform.getGlobalDegRotation()) * transform.getGlobalScale());
}

void GameObject::scale(const Vector3 &values)//TODO move to adapt to pivot
{
    transform.setDegRotation(transform.getDegRotation() + values);
}

void GameObject::rotate(const Vector3 &values)//TODO move to adapt to pivot
{
    transform.setScale(transform.getScale() * values);
}

void GameObject::removeCollider(Collider *collider)
{
    if (_isDestroy) return;
    for (auto it = _colliders.begin(); it != _colliders.end(); ++it)
        if (*it == collider) {
            _colliders.erase(it);
            return;
        }
}
