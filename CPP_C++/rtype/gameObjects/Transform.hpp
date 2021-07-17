/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Transform
*/

#pragma once

#include <algorithm>

#include "Vector2.hpp"

class Transform {
    public:
        Transform(Transform *parent=nullptr);
        Transform(const Vector3 &pos, const Vector3 &size, const Vector3 &pivot={0.5,0.5,0.5}, const Vector3 &rotate={0,0,0}, const Vector3 &scale={1,1,1});
        Transform(const Transform &other);
        ~Transform();

        Transform &operator=(const Transform &other);

        Vector3 getPosition() const { return pos; }
        Vector3 getGlobalPosition() const;
        Vector3 getSizeUnscaled() const { return size; }
        Vector3 getSize() const { return size * scale; }
        Vector3 getGlobalSize() const { return size * getGlobalScale(); }
        Vector3 getScale() const { return scale; }
        Vector3 getGlobalScale() const;
        Vector3 getDegRotation() const { return angle; }
        Vector3 getGlobalDegRotation() const;
        Vector3 getRadRotation() const { return { angle.x * M_PI / 180, angle.y * M_PI / 180, angle.z * M_PI / 180 }; }
        Vector3 getGlobalRadRotation() const;
        Vector3 getPivot() const { return pivot; }
        std::array<int64_t, 6> getLocalBounds() const; //x-min, y-min, z-min, x-max, y-max, z-max
        std::array<int64_t, 6> getGlobalBounds() const; //x-min, y-min, z-min, x-max, y-max, z-max

        void setPosition(const Vector3 &values) { pos = values; }
        void setGlobalPosition(const Vector3 &values);
        void setPivot(const Vector3 &values) { pivot = values; }
        void setSize(const Vector3 &values) { size = values; }
        void setGlobalSize(const Vector3 &values);
        void setScale(const Vector3 &values) { scale = values; }
        void setGlobalScale(const Vector3 &values);
        void setDegRotation(const Vector3 &values) { angle = values; }
        void setGlobalDegRotation(const Vector3 &values);
        void setRadRotation(const Vector3 &values);
        void setGlobalRadRotation(const Vector3 &values);

        void setParent(Transform *parent, bool keepOnGlobal=true);

    protected:
        Vector3 size;
        Vector3 pivot;

        Vector3 pos;
        Vector3 scale;
        Vector3 angle;
    
    private:
        Transform *parent;
};