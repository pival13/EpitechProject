/*
** EPITECH PROJECT, 2018
** cpp_rush1
** File description:
** Exercice 02
*/

#include <stdio.h>
#include "char.h"
#include "new.h"

typedef struct
{
    Class   base;
    char     x;
}   CharClass;

static void Char_ctor(CharClass *this, va_list *args)
{
    this->x = va_arg(*args, int);
    /* Fill this function for exercice 02 */
}

static void Char_dtor(CharClass *this)
{
    if (this == NULL)
        return;
}

static size_t determine_size_of_char(char number)
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

static char *Char_str(CharClass *this)
{
    size_t size = 5 + 2 + strlen(this->base.__name__) + \
determine_size_of_char(this->x);
    char *str = malloc(sizeof(char) * (size));

    if (str == NULL)
        raise("Memory error.\n");
    sprintf(str, "<%s (%c)>", this->base.__name__, this->x);
    return str;
}

// Operators

static CharClass *Char_add(const CharClass *this, const CharClass *other)
{
    return new(Char, this->x + other->x);
}

static CharClass *Char_sub(const CharClass *this, const CharClass *other)
{
    return new(Char, this->x - other->x);
}

static CharClass *Char_mul(const CharClass *this, const CharClass *other)
{
    return new(Char, this->x * other->x);
}

static CharClass *Char_div(const CharClass *this, const CharClass *other)
{
    return new(Char,
        ((other->x == 0) ? 0 : (this->x / other->x))
    );
}

// !Operators

// Comparators

static bool Char_eq(const CharClass * this, const CharClass * other)
{
    return this->x == other->x;
}

static bool Char_gt(const CharClass * this, const CharClass * other)
{
    return this->x > other->x;
}

static bool Char_lt(const CharClass * this, const CharClass * other)
{
    return this->x < other->x;
}

// !Comparators

// Create additional functions here

static const CharClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(CharClass),
        .__name__ = "Char",
        .__ctor__ = (ctor_t)&Char_ctor,
        .__dtor__ = (dtor_t)&Char_dtor,
        .__str__  = (to_string_t)&Char_str,
        .__add__  = (binary_operator_t)&Char_add,
        .__sub__  = (binary_operator_t)&Char_sub,
        .__mul__  = (binary_operator_t)&Char_mul,
        .__div__  = (binary_operator_t)&Char_div,
        .__eq__   = (binary_comparator_t)&Char_eq,
        .__gt__   = (binary_comparator_t)&Char_gt,
        .__lt__   = (binary_comparator_t)&Char_lt
    },
    .x = 0
};

const Class *Char = (const Class *)&_description;
