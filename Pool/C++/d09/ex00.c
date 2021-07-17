/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** ex00
*/

#include "ex00.h"

static void cthulhu_initializer ( cthulhu_t * this ) 
{
    this->m_name = "Cthulhu";
    this->m_power = 42;
}

cthulhu_t *new_cthulhu()
{
    cthulhu_t *c = malloc(sizeof(cthulhu_t));

    if (!c)
        return NULL;
    printf("----\nBuilding Cthulhu\n");
    cthulhu_initializer(c);
    return c;
}

void print_power(cthulhu_t *this)
{
    printf("Power => %d\n", this->m_power);
}

void attack(cthulhu_t *this)
{
    if (this->m_power >= 42) {
        printf("%s attacks and destroys the city\n", this->m_name);
        this->m_power -= 42;
    } else {
        printf("%s can't attack, he doesn't have enough power\n", this->m_name);
    }
}

void sleeping(cthulhu_t *this)
{
    printf("%s sleeps\n", this->m_name);
    this->m_power += 42000;
}

static void koala_initializer ( koala_t * this , char * _name , char _is_A_Legend ) 
{
    this->m_parent.m_name = _name;
    this->m_is_a_legend = _is_A_Legend;
    if (_is_A_Legend)
        this->m_parent.m_power = 42;
    else
        this->m_parent.m_power = 0;
}

koala_t *new_koala(char *name, char is_legend)
{
    koala_t *koala = malloc(sizeof(koala_t));

    if (!koala)
        return NULL;
    printf("----\nBuilding Cthulhu\nBuilding %s\n", name);
    koala_initializer(koala, name, is_legend);
    return koala;
}

void eat(koala_t *this)
{
    printf("%s eats\n", this->m_parent.m_name);
    this->m_parent.m_power += 42;
}