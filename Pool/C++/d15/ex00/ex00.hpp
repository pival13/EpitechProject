/*
** EPITECH PROJECT, 2020
** cpp_d15_2019 [WSL: Ubuntu]
** File description:
** ex00
*/

#pragma once

namespace {
    template<typename T>
    void swap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }
    
    template<typename T>
    T min(T a, T b)
    {
        return (a < b ? a : b);
    }
    
    template<typename T>
    T max(T a, T b)
    {
        return (a > b ? a : b);
    }
    
    template<typename T>
    T add(T a, T b)
    {
        return a + b;
    }
};