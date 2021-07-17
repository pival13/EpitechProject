/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Pizza
*/

#include "Pizza.hpp"

using namespace Plazza;

Pizza::Pizza(const std::string &_name, size_t cookTime, const std::vector<size_t> &ingredients)
: name(_name), _cookTime(cookTime), _ingredients(ingredients)
{}

Pizza::Pizza(const IPDataType &ipdata)
{
    setData(ipdata);
    unpack();
}

Pizza::Pizza(const Pizza &other, PizzaSize size)
{
    *this = other;
    _size = size;
    _cookTime *= PizzaFactory::getTimeMultiplier();
}

Pizza &Pizza::operator=(const Pizza &other)
{
    name = other.name;
    _cookTime = other._cookTime;
    _ingredients = other._ingredients;
    _size = other._size;
    setData(other.getData());
    return *this;
}

inline std::string Pizza::describe() const
{
    std::stringstream s;
    s << "Pizza \e[3m" << name << "\e[0m Size " << _size << " with ";
    for (size_t ing : _ingredients)
        s << (ing == _ingredients[0]? "":
             (ing == _ingredients[_ingredients.size()-1]? " and ": ", ")) +
             PizzaFactory::getIngredientName(ing);
    return s.str();
}

void Pizza::pack()
{
    IPDataType tbl(1 + name.length());

    tbl[0] = int8_t(_size);
    for (size_t i = 0; i != name.length(); i++)
        tbl[i+1] = name[i];
    setData(tbl);
}

void Pizza::unpack()
{
    IPDataType datas = getData();
    std::string name(reinterpret_cast<char*>(datas.data())+1, datas.size()-1);
    *this = *PizzaFactory::createPizza(name, static_cast<PizzaSize>(datas[0]));
}

std::ostream &operator<<(std::ostream &os, const Pizza &pizza)
{
    os << pizza.describe();
    return os;
}

std::ostream &operator<<(std::ostream &os, const PizzaSize &size)
{
    switch (size) {
        case PizzaSize::S:
            return os << "S";
        case PizzaSize::M:
            return os << "M";
        case PizzaSize::L:
            return os << "L";
        case PizzaSize::XL:
            return os << "XL";
        case PizzaSize::XXL:
            return os << "XXL";
        default:
            return os;
    }
}