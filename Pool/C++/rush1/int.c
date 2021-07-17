/*
** EPITECH PROJECT, 2018
** cpp_rush1
** File description:
** Exercice 02
*/

#include <stdio.h>
#include "int.h"
#include "new.h"

typedef struct
{
    Class   base;
    int     x;
}   IntClass;

static void Int_ctor(IntClass *this, va_list *args)
{
    this->x = va_arg(*args, int);
    /* Fill this function for exercice 02 */
}

static void Int_dtor(IntClass *this)
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

static char *Int_str(IntClass *this)
{
    size_t size = 5 + 2 + strlen(this->base.__name__) + \
determine_size_of_int(this->x);
    char *str = malloc(sizeof(char) * (size));

    if (str == NULL)
        raise("Memory error.\n");
    sprintf(str, "<%s (%d)>", this->base.__name__, this->x);
    return str;
}

// Operators

static IntClass *Int_add(const IntClass *this, const IntClass *other)
{
    return new(Int, this->x + other->x);
}

static IntClass *Int_sub(const IntClass *this, const IntClass *other)
{
    return new(Int, this->x - other->x);
}

static IntClass *Int_mul(const IntClass *this, const IntClass *other)
{
    return new(Int, this->x * other->x);
}

static IntClass *Int_div(const IntClass *this, const IntClass *other)
{
    return new(Int,
        ((other->x == 0) ? 0 : (this->x / other->x))
    );
}

// !Operators

// Comparators

static bool Int_eq(const IntClass * this, const IntClass * other)
{
    return this->x == other->x;
}

static bool Int_gt(const IntClass * this, const IntClass * other)
{
    return this->x > other->x;
}

static bool Int_lt(const IntClass * this, const IntClass * other)
{
    return this->x < other->x;
}

// !Comparators

// Create additional functions here

static const IntClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(IntClass),
        .__name__ = "Int",
        .__ctor__ = (ctor_t)&Int_ctor,
        .__dtor__ = (dtor_t)&Int_dtor,
        .__str__  = (to_string_t)&Int_str,
        .__add__  = (binary_operator_t)&Int_add,
        .__sub__  = (binary_operator_t)&Int_sub,
        .__mul__  = (binary_operator_t)&Int_mul,
        .__div__  = (binary_operator_t)&Int_div,
        .__eq__   = (binary_comparator_t)&Int_eq,
        .__gt__   = (binary_comparator_t)&Int_gt,
        .__lt__   = (binary_comparator_t)&Int_lt
    },
    .x = 0
};

const Class *Int = (const Class *)&_description;
