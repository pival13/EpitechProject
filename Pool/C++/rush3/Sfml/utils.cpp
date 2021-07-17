/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** utils
*/

template<typename T>
T myMap(const T value, const T range_min, const T range_max, const T newRange_min, const T newRange_max)
{
    T newValue = newRange_min + (newRange_max - newRange_min) * ((value - range_min) / (range_max - range_min));
    return (newValue);
}