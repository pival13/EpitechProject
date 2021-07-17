/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** IPObject
*/

#include "IPObject.hpp"

IPData::IPData()
: _data(sizeof(size_t), 0)
{
}

IPData::IPData(IPObject &obj)
{
    obj.pack();
    setData(obj.getData(), obj);
}

void IPData::setData(const IPDataType &data, const IPObject &obj)
{
    _data.resize(data.size() + sizeof(size_t));
    size_t type = typeid(obj).hash_code();
    for (int i = 0; i != sizeof(size_t); i++)
        _data[i] = ((type >> (i * 8)) & 0xFF);
    std::copy(data.begin(), data.end(), _data.begin()+sizeof(size_t));
}

IPDataType IPData::getData() const
{
    if (_data.size() < sizeof(size_t))
        return IPDataType();
    IPDataType v(_data.size() - sizeof(size_t));
    for (size_t i = 0; i != _data.size()-sizeof(size_t); i++)
        v[i] = _data[i+sizeof(size_t)];
    return v;
}