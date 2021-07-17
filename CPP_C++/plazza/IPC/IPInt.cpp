/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** IPInt
*/

#include "IPInt.hpp"

IPInt::IPInt(size_t a)
: _a(a)
{
}

IPInt::IPInt(const IPDataType &data)
{
    setData(data);
    unpack();
}

IPInt::operator size_t() const
{
    return _a;
}

void IPInt::pack()
{
    IPDataType v(sizeof(size_t));
    for (size_t i = 0; i != sizeof(size_t); i++)
        v[i] = (_a >> 8*i) & 0xFF;
    setData(v);
}

void IPInt::unpack()
{
    auto tbl = getData();
    _a = *(size_t*)tbl.data();
}

std::ostream &operator<<(std::ostream &os, const IPInt &a)
{
    size_t i = a;
    os << i;
    return os;
}