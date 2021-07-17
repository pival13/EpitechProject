/*
** EPITECH PROJECT, 2020
** list.c
** File description:
** rush1 ex06
*/

#include <stdlib.h>
#include <stdarg.h>
#include "raise.h"
#include "list.h"
#include "new.h"

typedef struct
{
    Container   base;
    Class       *_type;
    Object      *_value;
    Object      *_next;
    Object      *_prev;
}   ListClass;

typedef struct {
    Iterator    base;
    ListClass  *_list;
}   ListIteratorClass;

static void ListIterator_ctor(ListIteratorClass *this, va_list *args)
{
    this->_list = va_arg(*args, ListClass *);
    size_t pos = va_arg(*args, size_t);
    while (pos((Container *)this->_list) < pos)
        this->_list = this->_list->_next;
    while (pos((Container *)this->_list) > pos)
        this->_list = this->_list->_prev;
}

static bool ListIterator_eq(ListIteratorClass *this, ListIteratorClass *other)
{
    if (this == NULL || other == NULL)
        return false;
    return (pos((Container *)this->_list) == pos((Container *)other->_list));
}

static bool ListIterator_gt(ListIteratorClass *this, ListIteratorClass *other)
{
    if (this == NULL || other == NULL)
        return false;
    return (pos((Container *)this->_list) > pos((Container *)other->_list));
}

static bool ListIterator_lt(ListIteratorClass *this, ListIteratorClass *other)
{
    if (this == NULL || other == NULL)
        return false;
    return (pos((Container *)this->_list) < pos((Container *)other->_list));
}

static void ListIterator_incr(ListIteratorClass *this)
{
    this->_list = this->_list->_next;
}

static Object *ListIterator_getval(ListIteratorClass *this)
{
    if (this == NULL || this->_list == NULL)
        raise("Iterator is out of range");
    return this->_list->_value;
}

static void ListIterator_setval(ListIteratorClass *this, ...)
{
    va_list list;

    if (this == NULL || this->_list == NULL)
        raise("Iterator out of range");
    va_start(list, NULL);
    delete(this->_list->_value);
    this->_list->_value = va_new(this->_list->_type, &list);
    va_end(list);
}

static const ListIteratorClass   ListIteratorDescr = {
    {   /* Iterator struct */
        {   /* Class struct */
            .__size__ = sizeof(ListIteratorClass),
            .__name__ = "ListIterator",
            .__ctor__ = (ctor_t)&ListIterator_ctor,
            .__dtor__ = NULL,
            .__str__  = NULL,
            .__add__  = NULL,
            .__sub__  = NULL,
            .__mul__  = NULL,
            .__div__  = NULL,
            .__eq__   = (binary_comparator_t)&ListIterator_eq,
            .__gt__   = (binary_comparator_t)&ListIterator_gt,
            .__lt__   = (binary_comparator_t)&ListIterator_lt,
        },
        .__incr__   = (incr_t)&ListIterator_incr,
        .__getval__ = (getval_t)&ListIterator_getval,
        .__setval__ = (setval_t)&ListIterator_setval,
    },
    ._list = NULL
};

static const Class *ListIterator = (const Class *)&ListIteratorDescr;

static void List_ctor(ListClass *this, va_list *args)
{
    this->_type = va_arg(*args, Object *);
}

static void List_dtor(ListClass *this)
{
    ListClass *tmp;

    if (this == NULL)
        return;
    while (this->_prev != NULL) {
        tmp = this->_prev;
        this->_prev = ((ListClass *)this->_prev)->_prev;
        delete(tmp->_value);
        free(tmp);
    }
    while (this->_next != NULL) {
        tmp = this->_next;
        this->_next = ((ListClass *)this->_next)->_next;
        delete(tmp->_value);
        free(tmp);
    }
    delete(this->_value);
    this = NULL;
}

static char *List_str(ListClass *this)
{
    char *str = malloc(sizeof(char) * (strlen(this->base.base.__name__) + \
                       strlen(((Class *)this->_type)->__name__) + 6));
    char *str2;
    char *tmp;
    Object *it = begin((Container *)this);
    Object *it_end = end((Container *)this);

    if (str == NULL)
        raise("Memory error");
    sprintf(str, "<%s (%s)>", this->base.base.__name__, ((Class *)this->_type)->__name__);
    for (; lt(it, it_end); incr(it)) {
        tmp = str(((ListIteratorClass *)it)->_list->_value);
        str2 = malloc(sizeof(char) * (strlen(str) + strlen(tmp) + 6));
        if (str2 == NULL)
            raise("Memory error");
        strcpy(str2, str);
        strcat(str2, "\n    ");
        strcat(str2, tmp);
        free(str);
        free(tmp);
        str = str2;
    }
    str2 = malloc(sizeof(char) * (strlen(str) + strlen(this->base.base.__name__) + 5));
    if (str2 == NULL)
        raise("Memory error");
    strcpy(str2, str);
    strcat(str2, "\n</");
    strcat(str2, this->base.base.__name__);
    strcat(str2, ">");
    free(str);
    delete(it);
    delete(it_end);
    return str2;
}

static size_t List_len(ListClass *this)
{
    ListClass *tmp = this;
    size_t size = 0;

    while (tmp->_prev != NULL)
        tmp = tmp ->_prev;
    for (;tmp != NULL; tmp = tmp->_next, size++);
    return size - 1;
}

static size_t List_pos(ListClass *this)
{
    size_t pos = 0;
    ListClass *tmp = this;

    for(; tmp->_prev != NULL; tmp = tmp->_prev, ++pos);
    return pos;
}

static Iterator * List_begin(ListClass * this)
{
    return (new(ListIterator, this, 0));
}

static Iterator * List_end(ListClass *this)
{
    return new(ListIterator, this, len((Container *)this));
}

static void List_vaadditem(ListClass *this, size_t pos, va_list *list)
{
    ListClass *newlist;

    if (pos > len((Container *)this))
        raise("Index out of range");
    ListIteratorClass *tmp = new(ListIterator, this, pos);
    newlist = new(List, this->_type);
    newlist->_value = va_new(this->_type, list);
    newlist->_prev = tmp->_list->_prev;
    if (tmp->_list->_prev != NULL)
        ((ListClass *)tmp->_list->_prev)->_next = newlist;
    newlist->_next = tmp->_list;
    tmp->_list->_prev = newlist;
    delete(tmp);
}

static void List_additem(ListClass *this, ...)
{
    size_t pos;
    va_list list;

    va_start(list, NULL);
    pos = va_arg(list, size_t);
    if (pos > len((Container *)this))
        raise("Index out of range");
    List_vaadditem(this, pos, &list);
    va_end(list);
}

static void List_addAtFront(ListClass * this, ...)
{
    va_list list;

    va_start(list, NULL);
    List_vaadditem(this, 0, &list);
    va_end(list);
}

static void List_addAtBack(ListClass * this, ...)
{
    va_list list;

    va_start(list, NULL);
    List_vaadditem(this, len((Container *)this), &list);
    va_end(list);
}

static void List_delitem(ListClass *this, ...)
{
    va_list list;
    size_t p;

    va_start(list, NULL);
        p = va_arg(list, size_t);
        if (p >= len((Container *)this))
            raise("Index out of range");
        ListIteratorClass *tmp = new(ListIterator, this, p);
        if (tmp->_list == NULL)
            raise("Wrong Iterator.");
        this = tmp->_list->_next;
        if (tmp->_list->_prev != NULL)
            ((ListClass *)tmp->_list->_prev)->_next = tmp->_list->_next;
        ((ListClass *)tmp->_list->_next)->_prev = tmp->_list->_prev;
        delete(tmp->_list->_value);
        free(tmp->_list);
    va_end(list);
    delete(tmp);
}

static void List_delAtFront(ListClass * this)
{
    delitem((Container *)this, 0);
}

static void List_delAtBack(ListClass * this)
{
    delitem((Container *)this, len((Container *)this)-1);
}

static Object *List_getitem(ListClass *this, ...)
{
    va_list list;
    ListClass *tmp = this;
    size_t position = 0;

    va_start(list, NULL);
        position = va_arg(list, size_t);
        for (; pos((Container *)tmp) < position; tmp = tmp->_next);
        for (; pos((Container *)tmp) > position; tmp = tmp->_prev);
    va_end(list);
    return (tmp->_value);
}

static Object *List_front(ListClass * this, ...)
{
    return (getitem((Container *)this, 0));
}

static Object *List_back(ListClass * this, ...)
{
    return (getitem((Container *)this, len((Container *)this) - 1));
}

static void List_setitem(ListClass *this, ...)
{
    va_list list;
    size_t pos;

    if (this == NULL)
        raise("List is empty");
    va_start(list, NULL);
    pos = va_arg(list, size_t);
    if (pos >= len((Container *)this))
        raise("Index out of range");
    while (pos((Container *)this) < pos)
        this = this->_next;
    while (pos((Container *)this) > pos)
        this = this->_prev;
    delete(this->_value);
    this->_value = va_new(this->_type, &list);
    va_end(list);
}

static const ListClass   _descr = {
    {   /* Container struct */
        {   /* Class struct */
            .__size__ = sizeof(ListClass),
            .__name__ = "List",
            .__ctor__ = (ctor_t)&List_ctor,
            .__dtor__ = (dtor_t)&List_dtor,
            .__str__  = (to_string_t)&List_str,
            .__add__  = NULL,
            .__sub__  = NULL,
            .__mul__  = NULL,
            .__div__  = NULL,
            .__eq__   = NULL,
            .__gt__   = NULL,
            .__lt__   = NULL,
        },
        .__len__     = (len_t)&List_len,
        .__pos__     = (pos_t)&List_pos,
        .__begin__   = (iter_t)&List_begin,
        .__end__     = (iter_t)&List_end,
        .__getitem__ = (getitem_t)&List_getitem,
        .__setitem__ = (setitem_t)&List_setitem,
        .__additem__ = (additem_t)&List_additem,
        .__delitem__ = (delitem_t)&List_delitem,
        .__front__   = (getitem_t)&List_front,
        .__back__    = (getitem_t)&List_back,
        .__pushfront__ = (additem_t)&List_addAtFront,
        .__pushback__ = (additem_t)&List_addAtBack,
        .__popfront__ = (delitem_t)&List_delAtFront,
        .__popback__ = (delitem_t)&List_delAtBack,
        
    },
    ._type = NULL,
    ._value = NULL,
    ._next = NULL,
    ._prev = NULL
};

const Class   *List = (const Class *)&_descr;
