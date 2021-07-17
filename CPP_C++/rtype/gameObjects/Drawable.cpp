/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Drawable
*/

#include "Drawable.hpp"

Drawable::Drawable(const std::string &texturePath, const Vector2 &size, const Vector2 &offset, double rotate, const Vector2 &scale, GameObject* parent)
: Drawable
    ( texturePath
    , Transform
        ( offset
        , size
        , {0.5,0.5,0.5}
        , {0,0,rotate}
        , {scale.x,scale.y,1})
    , parent)
{
}

Drawable::Drawable(const std::string &filePath, const Transform &pTransform, GameObject *parent)
: GameObject(parent), texturePath(filePath), material(nullptr), _sprite(), materialRect(pTransform)
{
}

Drawable::~Drawable()
{
}

bool Drawable::setMaterial(Material *pMaterial)
{
    material = pMaterial;
    _sprite.setTexture(material->getTexture());
    if (materialRect.getSizeUnscaled().x < 0 || materialRect.getSizeUnscaled().y < 0)
        materialRect.setSize({double(material->getTexture().getSize().x), double(material->getTexture().getSize().y), 0});
    _sprite.setTextureRect(sf::IntRect(int(materialRect.getPosition().x), int(materialRect.getPosition().y), int(materialRect.getSizeUnscaled().x), int(materialRect.getSizeUnscaled().y)));
    _sprite.setOrigin(float(transform.getPivot().x*materialRect.getSizeUnscaled().x), float(transform.getPivot().y*materialRect.getSizeUnscaled().y));
    _sprite.setScale(float(materialRect.getScale().x), float(materialRect.getScale().y));
    return true;
}

const sf::Sprite &Drawable::getSprite()
{
    if (!_sprite.getTexture() && texturePath != "")
        setMaterial(Material::createMaterial(texturePath));
    return _sprite;
}

void Drawable::move(const Vector3 &dir)
{
    _sprite.move(float(dir.x), float(dir.y));
    GameObject::move(dir);
}

void Drawable::rotate(const Vector3 &degAngle)
{
    _sprite.rotate(float(degAngle.z));
    GameObject::rotate(degAngle);
}

void Drawable::scale(const Vector3 &scale)
{
    _sprite.scale(float(scale.x), float(scale.y));
    GameObject::scale(scale);
}

void Drawable::setPosition(const Vector3 &values)
{
    _sprite.setPosition(float(values.x), float(values.y));
    transform.setPosition(values);
}

void Drawable::setRotation(const Vector3 &values)
{
    _sprite.setRotation(float(values.z+materialRect.getDegRotation().z));
    transform.setDegRotation(values);
}

void Drawable::setScale(const Vector3 &values)
{
    _sprite.setScale(float(values.x*materialRect.getScale().x), float(values.y*materialRect.getScale().y));
    transform.setScale(values);
}

void Drawable::setOrigin(const Vector3 &values)
{
    _sprite.setOrigin(float(values.x), float(values.y));
    transform.setPivot(values);
}