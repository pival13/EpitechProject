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

#ifndef M_PI
    #define M_PI 3.14159265359
#endif

class Vector2;

class Vector3 {
    public:
        Vector3();
        Vector3(double x, double y, double z);
        Vector3(const Vector2 &v);
        Vector3(const Vector3 &v);
        ~Vector3();
        Vector3 &operator=(const Vector2 &other);
        Vector3 &operator=(const Vector3 &other);

        double magnitude() const;
        Vector3 rotate(const Vector3 &v) const;

        double operator[](size_t idx) const;
        double &operator[](size_t idx);
        Vector3 operator+(const Vector3 &other) const;
        Vector3 &operator+=(const Vector3 &other);
        Vector3 operator-(const Vector3 &other) const;
        Vector3 &operator-=(const Vector3 &other);
        Vector3 operator*(const Vector3 &other) const;
        Vector3 &operator*=(const Vector3 &other);
        Vector3 operator*(double v) const;
        Vector3 &operator*=(double v);
        Vector3 operator/(const Vector3 &other) const;
        Vector3 &operator/=(const Vector3 &other);
        Vector3 operator/(double v) const;
        Vector3 &operator/=(double v);

    public:
        double x;
        double y;
        double z;
};
std::ostream &operator<<(std::ostream &os, const Vector3 &v);