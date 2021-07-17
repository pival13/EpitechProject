/*
** EPITECH PROJECT, 2018
** cpp_rush1
** File description:
** Exercice 05
*/

#ifndef CONTAINER_H
# define CONTAINER_H

# include "object.h"
# include "iterator.h"
# include "raise.h"

typedef struct Container_s Container;

typedef Iterator *(*iter_t)(Container *this);
typedef size_t (*len_t)(Container *this);
typedef size_t (*pos_t)(Container *this);
typedef Object *(*getitem_t)(Container *this, ...);
typedef void (*setitem_t)(Container *this, ...);
typedef void (*additem_t)(Container *this, ...);
typedef void (*delitem_t)(Container *this, ...);

struct Container_s {
    Class       base;
    len_t       __len__;
    pos_t       __pos__;
    iter_t      __begin__;
    iter_t      __end__;
    getitem_t   __getitem__;
    setitem_t   __setitem__;
    additem_t   __additem__;
    delitem_t   __delitem__;
    getitem_t   __front__;
    getitem_t   __back__;
    additem_t   __pushfront__;
    additem_t   __pushback__;
    delitem_t   __popfront__;
    delitem_t   __popback__;
};

# define len(c)             ((Container *)c)->__len__(c)
# define pos(c)             ((Container *)c)->__pos__(c)
# define begin(c)           ((Container *)c)->__begin__(c)
# define end(c)             ((Container *)c)->__end__(c)
# define getitem(c, ...)    ((Container *)c)->__getitem__(c, __VA_ARGS__)
# define setitem(c, ...)    ((Container *)c)->__setitem__(c, __VA_ARGS__)
# define additem(c, ...)    ((Container *)c)->__additem__(c, __VA_ARGS__)
# define delitem(c, ...)    ((Container *)c)->__delitem__(c, __VA_ARGS__)
# define front(c)      ((Container *)c)->__front__(c)
# define back(c)       ((Container *)c)->__back__(c)
# define pushfront(c, ...)  ((Container *)c)->__pushfront__(c, __VA_ARGS__)
# define pushback(c, ...)   ((Container *)c)->__pushback__(c, __VA_ARGS__)
# define popfront(c)   ((Container *)c)->__popfront__(c)
# define popback(c)    ((Container *)c)->__popback__(c)

#endif
