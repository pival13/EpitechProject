/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

using namespace Plazza;

Fridge::Fridge(size_t initialSize, size_t _refreshTimeout)
: refreshTimeout(_refreshTimeout), lastRefresh(std::chrono::system_clock::now()), ingredients(initialSize, 5), _refreshThread([this]() { this->refresh(); })
{
}

Fridge::~Fridge()
{
    if (_refreshThread.joinable())
        _refreshThread.join();
}

void Fridge::takeIngredient(const std::vector<size_t> &iList)
{
    std::unique_lock<std::mutex> lck(fridgeAccess);
    do {
        if (*std::max_element(iList.begin(), iList.end()) >= ingredients.size())
            ingredients.insert(std::max_element(iList.begin(), iList.end()), 0);
        else if (std::all_of(iList.begin(), iList.end(), [this](size_t i) { return this->ingredients[i] != 0; })) {
            std::for_each(iList.begin(), iList.end(), [this](size_t i) { return this->ingredients[i]--; });
            break;
        }
    } while (!_closure && cvFridgeAccess.wait_until(lck, lastRefresh + std::chrono::milliseconds(10)) == std::cv_status::timeout);
}

void Fridge::refresh()
{
    std::unique_lock<std::mutex> lck(fridgeAccess);
    while (cvFridgeAccess.wait_for(lck, refreshTimeout) == std::cv_status::timeout) {
        lastRefresh = std::chrono::system_clock::now();
        for (auto &ingredient : ingredients)
            ingredient++;
    }
}

const std::string Fridge::status() const
{
    std::stringstream s;
    for (size_t i = 0; i != PizzaFactory::getIngredientNumber(); i++)
        s << (i == 0? "": "\n") << PizzaFactory::getIngredientName(i) << ": " << ingredients[i];
    return s.str();
}
