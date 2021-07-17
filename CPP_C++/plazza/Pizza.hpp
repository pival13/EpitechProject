/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Pizza
*/

#pragma once

#include <fstream>
#include <iostream>
#include <regex>

#include "IPC/IPObject.hpp"

namespace Plazza {
    enum IPCMessageKind
    {
        addOrder,
        addRecipe,
        getNbOrder,
        closure
    };

    enum PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    class Pizza : public IPObject {
        public:
            Pizza() = default;
            Pizza(const std::string &name, size_t cookTime, const std::vector<size_t> &ingredients);
            Pizza(const Pizza &other, PizzaSize size);
            Pizza(const IPDataType &ipdata);
            ~Pizza() = default;

            Pizza &operator=(const Pizza &other);

            inline size_t getCookTime() const { return _cookTime; }
            inline const std::vector<size_t> &getIngredients() const { return _ingredients; }
            std::string describe() const;

            void pack();
            void unpack();

            std::string name;
        private:
            size_t _cookTime;
            std::vector<size_t> _ingredients;
            PizzaSize _size;
    };

    class PizzaFactory {
        public:
            static void addNewPizza(const Pizza &pizza);
            static void addNewPizza(const std::string &name, size_t cookTime, const std::vector<std::string> &ingredients);
            static void addNewPizza(const std::string &pizzaDefinition);
            static void addNewPizzaFromFile(const std::string &plzFile);

            static inline void setTimeMultiplier(double mult) { _timeMultiplier = mult; }
            static inline double getTimeMultiplier() { return _timeMultiplier; }
            static inline size_t getIngredientNumber() { return _ingredients.size(); }
            static inline bool knownPizza(const std::string &name) { return std::any_of(_pizzas.begin(), _pizzas.end(), [&name](const Pizza &p) { return !strcasecmp(p.name.c_str(), name.c_str()); }); }

            static std::string status();
            static inline const std::string &getIngredientName(size_t ingredientNb) { return _ingredients.at(ingredientNb); }
            static std::unique_ptr<Pizza> createPizza(const std::string &name, PizzaSize size);

        private:
            static double _timeMultiplier;
            static std::vector<Pizza> _pizzas;
            static std::vector<std::string> _ingredients;
    };
};

std::ostream &operator<<(std::ostream &os, const Plazza::Pizza &pizza);
std::ostream &operator<<(std::ostream &os, const Plazza::PizzaSize &size);