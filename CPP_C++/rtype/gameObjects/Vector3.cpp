/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Vector2
*/

#include "Vector3.hpp"
#include "Vector2.hpp"

Vector3::Vector3() : Vector3(0,0,0) {}
Vector3::Vector3(double a, double b, double c) : x(a), y(b), z(c) {}
Vector3::Vector3(const Vector2 &v) { *this = v; }
Vector3::Vector3(const Vector3 &v) { *this = v; }
Vector3::~Vector3() {}

Vector3 &Vector3::operator=(const Vector2 &v) { x = v.x; y = v.y; z = 0; return *this; }
Vector3 &Vector3::operator=(const Vector3 &v) { x = v.x; y = v.y; z = v.z; return *this; }

double Vector3::magnitude() const { return std::sqrt(x*x+y*y+z*z); }

Vector3 Vector3::rotate(const Vector3 &v) const
{
    double sina = std::sin(v.x * M_PI / 180 );
    double sinb = std::sin(v.y * M_PI / 180 );
    double sinc = std::sin(v.z * M_PI / 180 );
    double cosa = std::cos(v.x * M_PI / 180 );
    double cosb = std::cos(v.y * M_PI / 180 );
    double cosc = std::cos(v.z * M_PI / 180 );
    return {
        cosc*cosb*x + (cosc*sinb*sina-sinc*cosa)*y + (cosc*sinb*cosa+sinc*sina)*z,
        sinc*cosb*x + (sinc*sinb*sina+cosc*cosa)*y + (sinc*sinb*cosa-cosc*sina)*z,
        -sinb*x + cosb*sina*y + cosb*cosa*z
    };
}

double &Vector3::operator[](size_t idx)
{
    switch (idx) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::invalid_argument("Expected 0, 1 or 2");
    }
}

double Vector3::operator[](size_t idx) const
{
    switch (idx) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::invalid_argument("Expected 0, 1 or 2");
    }
}

Vector3 Vector3::operator+(const Vector3 &v) const { Vector3 tmp = *this; return tmp += v; }
Vector3 &Vector3::operator+=(const Vector3 &v) { x += v.x; y += v.y; z += v.z; return *this; }
Vector3 Vector3::operator-(const Vector3 &v) const { Vector3 tmp = *this; return tmp -= v; }
Vector3 &Vector3::operator-=(const Vector3 &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
Vector3 Vector3::operator*(const Vector3 &v) const { Vector3 tmp = *this; return tmp *= v; }
Vector3 &Vector3::operator*=(const Vector3 &v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
Vector3 Vector3::operator*(double v) const { return operator*({v, v, v}); }
Vector3 &Vector3::operator*=(double v) { return operator*=({v, v, v}); }
Vector3 Vector3::operator/(const Vector3 &v) const { Vector3 tmp = *this; return tmp /= v; }
Vector3 &Vector3::operator/=(const Vector3 &v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
Vector3 Vector3::operator/(double v) const { return operator/({v, v, v}); }
Vector3 &Vector3::operator/=(double v) { return operator/=({v, v, v}); }

std::ostream &operator<<(std::ostream &os, const Vector3 &v) { return os << "{" << v.x << ", " << v.y << ", " << v.z << "}"; }