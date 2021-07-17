/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Vector2
*/

#include "Vector2.hpp"

Vector2::Vector2() : Vector2(0,0) {}
Vector2::Vector2(double a, double b) : x(a), y(b) {}
Vector2::Vector2(const Vector2 &v) { *this = v; }
Vector2::Vector2(const Vector3 &v) { *this = v; }
Vector2::~Vector2() {}

Vector2 &Vector2::operator=(const Vector2 &v) { x = v.x; y = v.y; return *this; }
Vector2 &Vector2::operator=(const Vector3 &v) { x = v.x; y = v.y; return *this; }

double Vector2::magnitude() const { return std::sqrt(x*x+y*y); }

Vector2 Vector2::rotate(double angle) const
{
    double sina = std::sin(angle * M_PI / 180 );
    double cosa = std::cos(angle * M_PI / 180 );
    return {
        cosa*x - sina*y,
        sina*x + cosa*y
    };
}

double &Vector2::operator[](size_t idx)
{
    switch (idx) {
        case 0: return x;
        case 1: return y;
        default: throw std::invalid_argument("Expected 0 or 1");
    }
}

double Vector2::operator[](size_t idx) const
{
    switch (idx) {
        case 0: return x;
        case 1: return y;
        default: throw std::invalid_argument("Expected 0 or 1");
    }
}

Vector2 Vector2::operator+(const Vector2 &v) const { Vector2 tmp = *this; return tmp += v; }
Vector2 &Vector2::operator+=(const Vector2 &v) { x += v.x; y += v.y; return *this; }
Vector2 Vector2::operator-(const Vector2 &v) const { Vector2 tmp = *this; return tmp -= v; }
Vector2 &Vector2::operator-=(const Vector2 &v) { x -= v.x; y -= v.y; return *this; }
Vector2 Vector2::operator*(const Vector2 &v) const { Vector2 tmp = *this; return tmp *= v; }
Vector2 &Vector2::operator*=(const Vector2 &v) { x *= v.x; y *= v.y; return *this; }
Vector2 Vector2::operator*(double v) const { return operator*({v, v}); }
Vector2 &Vector2::operator*=(double v) { return operator*=({v, v}); }
Vector2 Vector2::operator/(const Vector2 &v) const { Vector2 tmp = *this; return tmp /= v; }
Vector2 &Vector2::operator/=(const Vector2 &v) { x /= v.x; y /= v.y; return *this; }
Vector2 Vector2::operator/(double v) const { return operator/({v, v}); }
Vector2 &Vector2::operator/=(double v) { return operator/=({v, v}); }

std::ostream &operator<<(std::ostream &os, const Vector2 &v) { return os << "{" << v.x << ", " << v.y << "}"; }