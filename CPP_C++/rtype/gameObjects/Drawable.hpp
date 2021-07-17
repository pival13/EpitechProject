/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Drawable
*/

#pragma once

#include "GameObject.hpp"
#include "Material.hpp"

class Drawable : virtual public GameObject {
    public:
        Drawable(const std::string &texturePath="", const Vector2 &sizeInTexture={-1,-1}, const Vector2 &offsetInTexture={0,0}, double rotationofTexture=0, const Vector2 &scaleOfTexture={1,1}, GameObject* parent = nullptr);
        Drawable(const std::string &texturePath, const Transform& pTransform, GameObject* parent = nullptr);
        virtual ~Drawable();

        Material *getMaterial() { return material; }
        virtual const sf::Sprite &getSprite();

        virtual void move(const Vector3 &dir);
        virtual void scale(const Vector3 &scale);
        virtual void rotate(const Vector3 &degAngle);

        virtual void setPosition(const Vector3 &pos);
        virtual void setRotation(const Vector3 &angle);
        virtual void setScale(const Vector3 &scale);
        virtual void setOrigin(const Vector3 &origin);

        bool setMaterial(Material* pMaterial);
        bool setColor(sf::Color color) { _sprite.setColor(color); return true; }

    protected:
        std::string texturePath;
        Material *material;
        sf::Sprite _sprite;
        Transform materialRect;
};
