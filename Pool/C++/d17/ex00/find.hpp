/*
** EPITECH PROJECT, 2020
** cpp_d17_2019 [WSL: Ubuntu]
** File description:
** find
*/

#pragma once

#include <algorithm>

template<class T>
auto do_find(T &cont, int value) { return std::find(cont.begin(), cont.end(), value); }