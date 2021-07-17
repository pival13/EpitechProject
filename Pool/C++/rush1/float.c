/*
** EPITECH PROJECT, 2018
** cpp_rush1
** File description:
** Exercice 02
*/

#include <stdio.h>
#include "float.h"
#include "new.h"

typedef struct
{
    Class   base;
    float     x;
}   FloatClass;

static void Float_ctor(FloatClass *this, va_list *args)
{
    this->x = va_arg(*args, double);
}

static void Float_dtor(FloatClass *this)
{
    if (this == NULL)
        return;
}

static size_t determine_size_of_float(float number)
{
    size_t size = 7;

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

static char *Float_str(FloatClass *this)
{
    size_t size = 5 + 2 + strlen(this->base.__name__) + \
determine_size_of_float(this->x);
    char *str = malloc(sizeof(char) * (size));

    if (str == NULL)
        raise("Memory error.\n");
    sprintf(str, "<%s (%f)>", this->base.__name__, this->x);
    return str;
}

// Operators

static FloatClass *Float_add(const FloatClass *this, const FloatClass *other)
{
    return new(Float, this->x + other->x);
}

static FloatClass *Float_sub(const FloatClass *this, const FloatClass *other)
{
    return new(Float, this->x - other->x);
}

static FloatClass *Float_mul(const FloatClass *this, const FloatClass *other)
{
    return new(Float, this->x * other->x);
}

static FloatClass *Float_div(const FloatClass *this, const FloatClass *other)
{
    return new(Float,
        ((other->x == 0) ? 0 : (this->x / other->x))
    );
}

// !Operators

// Comparators

static bool Float_eq(const FloatClass * this, const FloatClass * other)
{
    return this->x == other->x;
}

static bool Float_gt(const FloatClass * this, const FloatClass * other)
{
    return this->x > other->x;
}

static bool Float_lt(const FloatClass * this, const FloatClass * other)
{
    return this->x < other->x;
}

// !Comparators

// Create additional functions here

static const FloatClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(FloatClass),
        .__name__ = "Float",
        .__ctor__ = (ctor_t)&Float_ctor,
        .__dtor__ = (dtor_t)&Float_dtor,
        .__str__  = (to_string_t)&Float_str,
        .__add__  = (binary_operator_t)&Float_add,
        .__sub__  = (binary_operator_t)&Float_sub,
        .__mul__  = (binary_operator_t)&Float_mul,
        .__div__  = (binary_operator_t)&Float_div,
        .__eq__   = (binary_comparator_t)&Float_eq,
        .__gt__   = (binary_comparator_t)&Float_gt,
        .__lt__   = (binary_comparator_t)&Float_lt
    },
    .x = 0
};

const Class *Float = (const Class *)&_description;
