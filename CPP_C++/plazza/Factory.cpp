/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Pizza
*/

#include "Pizza.hpp"

using namespace Plazza;

double PizzaFactory::_timeMultiplier;
std::vector<Pizza> PizzaFactory::_pizzas;
std::vector<std::string> PizzaFactory::_ingredients;

void PizzaFactory::addNewPizza(const Pizza &pizza)
{
    if (knownPizza(pizza.name))
        throw std::runtime_error("Pizza \"" + pizza.name + "\" redefine");
    else
        _pizzas.emplace_back(pizza);
}

void PizzaFactory::addNewPizza(const std::string &name, size_t cookTime, const std::vector<std::string> &ingredients)
{
    std::vector<size_t> pizzaIngredients;
    for (std::string ing : ingredients) {
        auto it = std::find(_ingredients.begin(), _ingredients.end(), ing);
        if (it == _ingredients.end()) {
            _ingredients.push_back(ing);
            pizzaIngredients.push_back(_ingredients.size()-1);
        } else
            pizzaIngredients.push_back(it - _ingredients.begin());
    }
    addNewPizza(Pizza(name, cookTime, pizzaIngredients));
}

void PizzaFactory::addNewPizza(const std::string &pizzaDefinition)
{
    std::smatch match;
    if (std::regex_match(pizzaDefinition, match, std::regex("\\s*(\\w+)\\s+(\\d+)\\s+((?:\\s*\\w+)+)\\s*"))) {
        std::vector<std::string> pizzaIngredients;
        for (size_t i = 0; i != std::string::npos; i = match[3].str().find_first_of(' ', i+1))
            pizzaIngredients.push_back(match[3].str().substr(i == 0 ? i : i+1, match[3].str().find_first_of(' ', i+1)-(i == 0 ? i : i+1)));
        addNewPizza(match[1].str(), std::stoul(match[2].str()), pizzaIngredients);
    } else
        throw std::runtime_error("Invalid pizza definition");
}

void PizzaFactory::addNewPizzaFromFile(const std::string &plzFile)
{
    std::ifstream f(plzFile);
    if (!f.is_open())
        throw std::runtime_error("Can't state file \"" + plzFile + "\"");
    while (!f.eof()) {
        std::string line;
        std::getline(f, line);
        if (!std::regex_match(line, std::regex("\\s*(#.*)?")))
            addNewPizza(line);
    }
    f.close();
}

std::unique_ptr<Pizza> PizzaFactory::createPizza(const std::string &name, PizzaSize size)
{
    return std::make_unique<Pizza>(Pizza(
        *std::find_if(_pizzas.begin(), _pizzas.end(), [&name](const Pizza &p) {
            return !strcasecmp(p.name.c_str(), name.c_str());
        }), size)
    );
}

std::string PizzaFactory::status()
{
    std::stringstream s;
    s << "Pizzas available:\n";
    for (auto pizza : _pizzas)
        s << (pizza.name == _pizzas[0].name? "": "\n") << "\t\e[3m" << pizza.name << "\e[0m, cooking time: " << pizza.getCookTime() * _timeMultiplier / 1000 << "s";
    return s.str();
}
