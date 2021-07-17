/*
** EPITECH PROJECT, 2020
** cpp_d15_2019 [WSL: Ubuntu]
** File description:
** ex02
*/

#pragma once

#include <iostream>

template<typename T>
T min(T a, T b)
{
    std::cout << "template min" << std::endl;
    return (a < b ? a : b);
}

int min(int a, int b)
{
    std::cout << "non-template min" << std::endl;
    return (a < b ? a : b);
}

template<typename T>
T templateMin(T *arr, size_t size)
{
    T m = arr[0];

    for (size_t i = 1; i < size; i++)
        m = min<T>(m, arr[i]);
    return m;
}

int nonTemplateMin(int *arr, size_t size)
{
    int m = arr[0];

    for (size_t i = 1; i < size; i++)
        m = min(m, arr[i]);
    return m;
}