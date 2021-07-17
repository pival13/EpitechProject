/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** IPObject
*/

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

class IPObject;

typedef std::vector<int8_t> IPDataType;

struct IPData {
    IPData();
    IPData(IPObject &obj);
    ~IPData() = default;

    IPDataType _data;

    template<class T> inline bool isType(const T &_class) const { return isType(typeid(T)); }
    inline bool isType(const std::type_info &typeInfo) const { return !_data.empty() && typeInfo.hash_code() == *reinterpret_cast<const size_t*>(_data.data()); }
    IPDataType getData() const;
    protected: void setData(const IPDataType &data, const IPObject &obj);
};

class IPObject : private IPData {
    public:
        ~IPObject() = default;

        virtual void pack() = 0;
        virtual void unpack() = 0;
        template<class T> inline bool isType(const T &_class) const { return IPData::isType(_class); }
        inline IPDataType getData() const { return IPData::getData(); }

    protected:
        inline void setData(const IPDataType &data) { return IPData::setData(data, *this); }
};
