/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** IPString
*/

#include "IPString.hpp"

IPString::IPString(const std::string &s)
: _s(s)
{
}

IPString::IPString(const IPDataType &data)
{
    setData(data);
    unpack();
}

IPString::operator std::string() const
{
    return _s;
}

void IPString::pack()
{
    IPDataType v(_s.size());
    for (size_t i = 0; i != _s.size(); i++)
        v[i] = _s[i];
    setData(v);
}

void IPString::unpack()
{
    auto tbl = getData();
    _s.resize(tbl.size());
    for (size_t i = 0; i != tbl.size(); i++)
        _s[i] = tbl[i];
}

std::ostream &operator<<(std::ostream &os, const IPString &s)
{
    std::string str = s;
    os << str;
    return os;
}