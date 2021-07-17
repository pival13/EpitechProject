/*
** EPITECH PROJECT, 2018
** cpp_rush1
** File description:
** Exercice 02
*/

#include <stdio.h>
#include "point.h"
#include "new.h"

typedef struct
{
    Class   base;
    int     x, y;
}   PointClass;

static void Point_ctor(PointClass *this, va_list *args)
{
    this->x = va_arg(*args, int);
    this->y = va_arg(*args, int);
    /* Fill this function for exercice 02 */
}

static void Point_dtor(PointClass *this)
{
    if (this == NULL)
        return;
}

static size_t determine_size_of_int(int number)
{
    size_t size = 1;

    if (number < 0) {
        ++size;
        number = -number;
    }
    while (number > 10) {
        number /= 10;
        ++size;
    }
    return size;
}

static char *Point_str(PointClass *this)
{
    unsigned int size = 7 + 2 + strlen(this->base.__name__) + \
determine_size_of_int(this->x) + determine_size_of_int(this->y);
    char *str = malloc(sizeof(char) * (size));

    if (str == NULL)
        raise("Memory error.\n");
    sprintf(str, "<%s (%d, %d)>", this->base.__name__, this->x, this->y);
    return str;
}

// Operators
static float sqrt2(float x)
{
    double root=x/3;
    int i;
    if (x <= 0) return 0;
    for (i=0; i<32; i++)
        root = (root + x / root) / 2;
    return root;
}

static PointClass *Point_add(const PointClass *this, const PointClass *other)
{
    return new(Point, this->x + other->x, this->y + other->y);
}

static PointClass *Point_sub(const PointClass *this, const PointClass *other)
{
    return new(Point, this->x - other->x, this->y - other->y);
}

static PointClass *Point_mul(const PointClass *this, const PointClass *other)
{
    return new(Point, this->x * other->x, this->y * other->y);
}

static PointClass *Point_div(const PointClass *this, const PointClass *other)
{
    return new(Point,
        ((other->x == 0) ? 0 : (this->x / other->x)),
        ((other->y == 0) ? 0 : (this->y / other->y))
    );
}

// !Operators

// Comparators

static bool Point_eq(const PointClass * this, const PointClass * other)
{
    if (this->x != other->x)
        return false;
    if (this->y != other->y)
        return false;
    return true;
}

static bool Point_gt(const PointClass * this, const PointClass * other)
{
    double thisRet = sqrt2(this->x*this->x + this->y*this->y);
    double otherRet = sqrt2(other->x*other->x + other->y*other->y);

    if (thisRet > otherRet)
        return true;
    return false;
}

static bool Point_lt(const PointClass * this, const PointClass * other)
{
    if (!Point_gt(this, other) && !Point_eq(this, other))
        return true;
    return false;
}

// !Comparators

// Create additional functions here

static const PointClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(PointClass),
        .__name__ = "Point",
        .__ctor__ = (ctor_t)&Point_ctor,
        .__dtor__ = (dtor_t)&Point_dtor,
        .__str__  = (to_string_t)&Point_str,
        .__add__  = (binary_operator_t)&Point_add,
        .__sub__  = (binary_operator_t)&Point_sub,
        .__mul__  = (binary_operator_t)&Point_mul,
        .__div__  = (binary_operator_t)&Point_div,
        .__eq__   = (binary_comparator_t)&Point_eq,
        .__gt__   = (binary_comparator_t)&Point_gt,
        .__lt__   = (binary_comparator_t)&Point_lt
    },
    .x = 0,
    .y = 0
};

const Class *Point = (const Class *)&_description;
