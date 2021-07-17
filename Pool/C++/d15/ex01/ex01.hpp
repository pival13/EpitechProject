/*
** EPITECH PROJECT, 2020
** cpp_d15_2019 [WSL: Ubuntu]
** File description:
** ex01
*/

#pragma once

template<typename T>
int compare(const T &a, const T &b)
{
    if (a == b)
        return 0;
    else if (a < b)
        return -1;
    else
        return 1;
}
