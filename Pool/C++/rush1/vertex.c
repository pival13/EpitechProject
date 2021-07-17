/*
** EPITECH PROJECT, 2018
** cpp_rush1
** File description:
** Exercice 02
*/

#include "vertex.h"
#include "new.h"

#include <stdio.h>
#include <string.h>

typedef struct {
    Class base;
    int x, y, z;
} VertexClass;

// Constructor, Destructor

static void Vertex_ctor(VertexClass *this, va_list *args)
{
    this->x = va_arg(*args, int);
    this->y = va_arg(*args, int);
    this->z = va_arg(*args, int);
}

static void Vertex_dtor(VertexClass *this)
{
    if (this == NULL)
        return;
}

// !Constructor, Destructor

// Comparators

static float sqrt2(float x)
{
    double root=x/3;
    int i;
    if (x <= 0) return 0;
    for (i=0; i<32; i++)
        root = (root + x / root) / 2;
    return root;
}

static bool Vertex_eq(const VertexClass *this, const VertexClass *other)
{
    if (other->x != this->x)
        return (false);
    if (other->y != this->y)
        return (false);
    if (other->z != this->z)
        return (false);
    return (true);
}

static bool Vertex_gt(const VertexClass *this, const VertexClass *other)
{
    double thisRet = sqrt2(this->x*this->x + this->y*this->y + this->z*this->z);
    double otherRet = sqrt2(other->x*other->x + other->y*other->y + other->z*other->z);

    if (thisRet > otherRet)
        return true;
    return false;
}

static bool Vertex_lt(const VertexClass *this, const VertexClass *other)
{
    if (!Vertex_gt(this, other) && !Vertex_eq(this, other))
        return (true);
    return (false);
}

// !Comparators

// Operators


static VertexClass * Vertex_add(const VertexClass *this, const VertexClass *other)
{
    VertexClass *newObj = new(Vertex,
        this->x + other->x,
        this->y + other->y,
        this->z + other->z
    );
    return (newObj);
}

static VertexClass * Vertex_sub(const VertexClass * this, const VertexClass * other)
{
    VertexClass * newObj = new (Vertex,
        this->x - other->x,
        this->y - other->y,
        this->z - other->z
    );
    return (newObj);
}

static VertexClass *Vertex_mul(const VertexClass *this, const VertexClass *other)
{
    VertexClass *new_obj = new(Vertex,
        this->x * other->x,
        this->y * other->y,
        this->z * other->z
    );
    return new_obj;
}

static VertexClass *Vertex_div(const VertexClass *this, const VertexClass *other)
{
    VertexClass *new_obj = new(Vertex,
        (other->x == 0) ? (0) : (this->x / other->x),
        (other->y == 0) ? (0) : (this->y / other->y),
        (other->z == 0) ? (0) : (this->z / other->z)
    );
    return new_obj;
}

// !Operators

// Str

static size_t intLen(int nb)
{
    size_t size = 1;

    if (nb < 0) {
        size = 2;
        nb = -nb;
    }
    while (nb > 10)
    {
        nb /= 10;
        ++size;
    }
    return (size);
}

static char *Vertex_str(VertexClass *this)
{
    // 9 : chars constantes, 1 : '\0', length name and length x y z
    size_t size = 9 + 1 + strlen(this->base.__name__) + intLen(this->x) + intLen(this->y) + intLen(this->z);
    char *rep = malloc(sizeof(char) * (size));

    if (rep == NULL)
        raise("Memory Error.\n");
    sprintf(rep, "<%s (%d, %d, %d)>", this->base.__name__, this->x, this->y, this->z);
    return (rep);
}

// !Str

// Create additional functions here

static const VertexClass _description = {
    {/* Class struct */
     .__size__ = sizeof(VertexClass),
     .__name__ = "Vertex",
     .__ctor__ = (ctor_t)&Vertex_ctor,
     .__dtor__ = (dtor_t)&Vertex_dtor,
     .__str__ = (to_string_t)&Vertex_str,       /* Implement this method for exercice 02 */
     .__add__ = (binary_operator_t)&Vertex_add, /* Implement this method for exercice 03 */
     .__sub__ = (binary_operator_t)&Vertex_sub, /* Implement this method for exercice 03 */
     .__mul__ = (binary_operator_t)&Vertex_mul,
     .__div__ = (binary_operator_t)&Vertex_div,
     .__eq__ = (binary_comparator_t)&Vertex_eq,
     .__gt__ = (binary_comparator_t)&Vertex_gt,
     .__lt__ = (binary_comparator_t)&Vertex_lt},
    .x = 0,
    .y = 0,
    .z = 0
};

const Class *Vertex = (const Class *)&_description;
