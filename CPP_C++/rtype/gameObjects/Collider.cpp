/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Collider
*/

#include "Collider.hpp"

Collider::Collider(GameObject &attachOn) : Collider(attachOn, Transform()) {}
Collider::Collider(GameObject &attachOn, const Vector3 &size, const Vector3 &pos, const Vector3 &pivot, const Vector3 &rotate, const Vector3 &scale)
: Collider(attachOn, Transform(pos, size, pivot, rotate, scale)) {}
Collider::Collider(GameObject &attachOn, const Transform &colliderData)
: gameObject(attachOn), transform(colliderData)
{
    transform.setParent(&attachOn.getTransform(), false);
    attachOn.addCollider(this);
}

Collider::~Collider()
{
    gameObject.removeCollider(this);
}

void Collider::checkBoundary(const std::list<Collider *> &colliders)
{
    GameObject *parent = gameObject.getParent();
    while (parent && parent->getParent()) parent = parent->getParent();
    for (Collider *c : colliders) {
        if (&gameObject == &c->gameObject)
            continue;
        GameObject *cParent = c->gameObject.getParent();
        while (cParent && cParent->getParent()) cParent = cParent->getParent();
        if (&gameObject == &c->gameObject || parent != cParent) continue;
        else if (onCollision && *this == *c) onCollision(*c);
    }
}

bool Collider::operator==(const Collider &other)
{
    auto pos = transform.getGlobalPosition();
    auto size = transform.getGlobalSize();
    double maxLen = size.magnitude();
    std::array<double, 6> myBounds = { pos.x-maxLen, pos.y-maxLen, pos.z-maxLen,
                                       pos.x+maxLen, pos.y+maxLen, pos.z+maxLen };

    pos = other.transform.getGlobalPosition();
    size = other.transform.getGlobalSize();
    maxLen = size.magnitude();
    std::array<double, 6> otherBounds = { pos.x-maxLen, pos.y-maxLen, pos.z-maxLen,
                                          pos.x+maxLen, pos.y+maxLen, pos.z+maxLen };

    if (( (myBounds[0] >= otherBounds[0] && myBounds[0] <= otherBounds[3]) ||
          (otherBounds[0] >= myBounds[0] && otherBounds[0] <= myBounds[3]) ) &&//Check X
        ( (myBounds[1] >= otherBounds[1] && myBounds[1] <= otherBounds[4]) ||
          (otherBounds[1] >= myBounds[1] && otherBounds[1] <= myBounds[4]) ) &&//Check Y
        ( (myBounds[2] >= otherBounds[2] && myBounds[2] <= otherBounds[5]) ||
          (otherBounds[2] >= myBounds[2] && otherBounds[2] <= myBounds[5]) )) {//Check Z
        //Bounds overlapping
            auto myTBounds = transform.getGlobalBounds();
            auto otherTBounds = other.transform.getGlobalBounds();
            
            if (( (myTBounds[0] >= otherTBounds[0] && myTBounds[0] <= otherTBounds[3]) ||
                  (otherTBounds[0] >= myTBounds[0] && otherTBounds[0] <= myTBounds[3]) ) &&//Check X
                ( (myTBounds[1] >= otherTBounds[1] && myTBounds[1] <= otherTBounds[4]) ||
                  (otherTBounds[1] >= myTBounds[1] && otherTBounds[1] <= myTBounds[4]) ) &&//Check Y
                ( (myTBounds[2] >= otherTBounds[2] && myTBounds[2] <= otherTBounds[5]) ||
                  (otherTBounds[2] >= myTBounds[2] && otherTBounds[2] <= myTBounds[5]) )) {//Check Z
                    //TODO improve
                    //auto v = getCollisionDetectorVector();
                    //auto v2 = other.getCollisionDetectorVector();
                    //if (v.size() == 0 && v2.size() == 0) {
                    //    
                    //} else if (v.size() < v2.size()) {
                    //
                    //} else {
                    //
                    //}
                    return true;
                  }
    }
    return false;
}