/*
** EPITECH PROJECT, 2020
** cpp_d15_2019 [WSL: Ubuntu]
** File description:
** ex04
*/

#include "ex04.hpp"
/**/
template<class T>
bool equal(const T &a, const T &b) { return a == b; }

template bool equal<int>(const int &a, const int &b);
template bool equal<float>(const float &a, const float &b);
template bool equal<double>(const double &a, const double &b);
template bool equal<std::string>(const std::string &a, const std::string &b);

template<class T>
bool Tester<T>::equal(const T &a, const T &b) { return a == b; }

template class Tester<int>;
template class Tester<float>;
template class Tester<double>;
template class Tester<std::string>;
/*/
template<>
bool equal<int>(const int &a, const int &b)
{
    return a == b;
}

template<>
bool equal<float>(const float &a, const float &b)
{
    return a == b;
}

template<>
bool equal<double>(const double &a, const double &b)
{
    return a == b;
}

template<>
bool equal<std::string>(const std::string &a, const std::string &b)
{
    return a == b;
}

template<>
bool Tester<int>::equal(const int &a, const int &b)
{
    return a == b;
}

template<>
bool Tester<float>::equal(const float &a, const float &b)
{
    return a == b;
}

template<>
bool Tester<double>::equal(const double &a, const double &b)
{
    return a == b;
}

template<>
bool Tester<std::string>::equal(const std::string &a, const std::string &b)
{
    return a == b;
}/**/