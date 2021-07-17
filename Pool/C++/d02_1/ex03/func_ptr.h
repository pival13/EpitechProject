/*
** EPITECH PROJECT, 2020
** funct_ptr.h
** File description:
** header of func ptr
*/

#ifndef FUNC_PTR_H
#define FUNC_PTR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "func_ptr_enum.h"

void print_normal(const char *str);
void print_reverse(const char *str);
void print_upper(const char *str);
void print_42(const char *str);
void do_action(action_t action, const char *str);

#endif

