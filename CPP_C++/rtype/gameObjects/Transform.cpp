/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Transform
*/

#include "Transform.hpp"

Transform::Transform(Transform *_parent)
: Transform({0, 0, 0}, {1, 1, 1}) { parent = _parent; }
Transform::Transform(const Vector3 &_pos, const Vector3 &_size, const Vector3 &_pivot, const Vector3 &_rotate, const Vector3 &_scale)
: size(_size), pivot(_pivot), pos(_pos), scale(_scale), angle(_rotate), parent(nullptr)
{
}

Transform::~Transform()
{
}

Transform::Transform(const Transform &other) : Transform() { *this = other; }
Transform &Transform::operator=(const Transform &other)
{
    parent = other.parent;
    size = other.size;
    pivot = other.pivot;
    pos = other.pos;
    scale = other.scale;
    angle = other.angle;
    return *this;
}

void Transform::setParent(Transform *_parent, bool globalRelatif)
{
    if (!globalRelatif || _parent == nullptr || parent == nullptr)
        parent = _parent;
    else {
        //TODO add relativness
        parent = _parent;
    }
}

Vector3 Transform::getGlobalPosition() const
{
    if (!parent) return getPosition();
    return parent->getGlobalPosition() + getPosition();
}

Vector3 Transform::getGlobalScale() const
{
    if (!parent) return getScale();
    return parent->getGlobalScale() * getScale();
}

Vector3 Transform::getGlobalDegRotation() const
{
    if (!parent) return getDegRotation();
    return parent->getGlobalDegRotation() + getDegRotation();
}

Vector3 Transform::getGlobalRadRotation() const
{
    if (!parent) return getRadRotation();
    return parent->getGlobalRadRotation() + getRadRotation();
}

std::array<int64_t, 6> Transform::getLocalBounds() const
{
    Vector3 position = getPosition();
    Vector3 dimension = getSize();
    Vector3 origin = getPivot();
    Vector3 rotate = getDegRotation();

    Vector3 p000(position.x - dimension.x * origin.x, position.y - dimension.y * origin.y, position.z - dimension.z * origin.z);
    Vector3 p111(p000.x + dimension.x, p000.y + dimension.y, p000.z + dimension.z);
    Vector3 p001 = position + Vector3(p000.x-position.x, p000.y-position.y, p111.z-position.z).rotate(rotate);
    Vector3 p010 = position + Vector3(p000.x-position.x, p111.y-position.y, p000.z-position.z).rotate(rotate);
    Vector3 p011 = position + Vector3(p000.x-position.x, p111.y-position.y, p111.z-position.z).rotate(rotate);
    Vector3 p100 = position + Vector3(p111.x-position.x, p000.y-position.y, p000.z-position.z).rotate(rotate);
    Vector3 p101 = position + Vector3(p111.x-position.x, p000.y-position.y, p111.z-position.z).rotate(rotate);
    Vector3 p110 = position + Vector3(p111.x-position.x, p111.y-position.y, p000.z-position.z).rotate(rotate);

    p000 = position + Vector3(dimension.x*-origin.x, dimension.y*-origin.y, dimension.z*-origin.z).rotate(rotate);
    p111 = position + Vector3(dimension.x*(1-origin.x), dimension.y*(1-origin.y), dimension.z*(1-origin.z)).rotate(rotate);

    return {
        int64_t(std::min({p000.x, p001.x, p010.x, p011.x, p100.x, p101.x, p110.x, p111.x})),
        int64_t(std::min({p000.y, p001.y, p010.y, p011.y, p100.y, p101.y, p110.y, p111.y})),
        int64_t(std::min({p000.z, p001.z, p010.z, p011.z, p100.z, p101.z, p110.z, p111.z})),
        int64_t(std::max({p000.x, p001.x, p010.x, p011.x, p100.x, p101.x, p110.x, p111.x})),
        int64_t(std::max({p000.y, p001.y, p010.y, p011.y, p100.y, p101.y, p110.y, p111.y})),
        int64_t(std::max({p000.z, p001.z, p010.z, p011.z, p100.z, p101.z, p110.z, p111.z}))
    };
}

std::array<int64_t, 6> Transform::getGlobalBounds() const
{
    Vector3 position = getGlobalPosition();
    Vector3 dimension = getGlobalSize();
    Vector3 origin = getPivot();
    Vector3 rotate = getGlobalDegRotation();

    Vector3 p000(position.x - dimension.x * origin.x, position.y - dimension.y * origin.y, position.z - dimension.z * origin.z);
    Vector3 p111(p000.x + dimension.x, p000.y + dimension.y, p000.z + dimension.z);
    Vector3 p001 = position + Vector3(p000.x-position.x, p000.y-position.y, p111.z-position.z).rotate(rotate);
    Vector3 p010 = position + Vector3(p000.x-position.x, p111.y-position.y, p000.z-position.z).rotate(rotate);
    Vector3 p011 = position + Vector3(p000.x-position.x, p111.y-position.y, p111.z-position.z).rotate(rotate);
    Vector3 p100 = position + Vector3(p111.x-position.x, p000.y-position.y, p000.z-position.z).rotate(rotate);
    Vector3 p101 = position + Vector3(p111.x-position.x, p000.y-position.y, p111.z-position.z).rotate(rotate);
    Vector3 p110 = position + Vector3(p111.x-position.x, p111.y-position.y, p000.z-position.z).rotate(rotate);

    p000 = position + Vector3(dimension.x*-origin.x, dimension.y*-origin.y, dimension.z*-origin.z).rotate(rotate);
    p111 = position + Vector3(dimension.x*(1-origin.x), dimension.y*(1-origin.y), dimension.z*(1-origin.z)).rotate(rotate);

    return {
        int64_t(std::min({p000.x, p001.x, p010.x, p011.x, p100.x, p101.x, p110.x, p111.x})),
        int64_t(std::min({p000.y, p001.y, p010.y, p011.y, p100.y, p101.y, p110.y, p111.y})),
        int64_t(std::min({p000.z, p001.z, p010.z, p011.z, p100.z, p101.z, p110.z, p111.z})),
        int64_t(std::max({p000.x, p001.x, p010.x, p011.x, p100.x, p101.x, p110.x, p111.x})),
        int64_t(std::max({p000.y, p001.y, p010.y, p011.y, p100.y, p101.y, p110.y, p111.y})),
        int64_t(std::max({p000.z, p001.z, p010.z, p011.z, p100.z, p101.z, p110.z, p111.z}))
    };
}