/*
** EPITECH PROJECT, 2020
** new.c
** File description:
** implement new and delete
*/

#include "new.h"

Object *new(const Class *class, ...)
{
    Class *ptr = malloc(class->__size__);
    va_list list;

    if (ptr == NULL)
        raise("Memory Error");
    ptr = memcpy(ptr, class, class->__size__);
    va_start(list, NULL);
    if (ptr->__ctor__ != NULL)
        ptr->__ctor__(ptr, &list);
    va_end(list);
    return ptr;
}

Object *va_new(const Class *class, va_list* list)
{
    Class *ptr = malloc(class->__size__);

    if (ptr == NULL)
        raise("Memory Error");
    ptr = memcpy(ptr, class, class->__size__);
    if (ptr->__ctor__ != NULL)
        ptr->__ctor__(ptr, list);
    return ptr;
}

void delete(Object *ptr)
{
    if (ptr == NULL)
        return;
    if (((Class *)ptr)->__dtor__ != NULL)
        ((Class *)ptr)->__dtor__(ptr);
    free(ptr);
    ptr = NULL;
}
