/*
** EPITECH PROJECT, 2020
** cpp_d15_2019 [WSL: Ubuntu]
** File description:
** ex03
*/

#pragma once

#include <iostream>

template<typename T>
void print(const T &a)
{
    std::cout << a << std::endl;
}

template<typename T>
void foreach(T *arr, void (*f)(const T &), size_t size)
{
    for (size_t i = 0; i < size; i++)
        f(arr[i]);
}