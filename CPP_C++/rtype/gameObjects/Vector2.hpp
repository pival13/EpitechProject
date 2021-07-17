/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Vector2
*/

#pragma once

#include <iostream>
#include <cstdint>
#include <array>
#include <cmath>

#include "Vector3.hpp"

class Vector2 {
    public:
        Vector2();
        Vector2(double x, double y);
        Vector2(const Vector2 &v);
        Vector2(const Vector3 &v);
        ~Vector2();
        Vector2 &operator=(const Vector2 &other);
        Vector2 &operator=(const Vector3 &other);

        double magnitude() const;
        Vector2 rotate(double angle) const;

        double operator[](size_t idx) const;
        double &operator[](size_t idx);
        Vector2 operator+(const Vector2 &other) const;
        Vector2 &operator+=(const Vector2 &other);
        Vector2 operator-(const Vector2 &other) const;
        Vector2 &operator-=(const Vector2 &other);
        Vector2 operator*(const Vector2 &other) const;
        Vector2 &operator*=(const Vector2 &other);
        Vector2 operator*(double v) const;
        Vector2 &operator*=(double v);
        Vector2 operator/(const Vector2 &other) const;
        Vector2 &operator/=(const Vector2 &other);
        Vector2 operator/(double v) const;
        Vector2 &operator/=(double v);

    public:
        double x;
        double y;
};
std::ostream &operator<<(std::ostream &os, const Vector2 &v);