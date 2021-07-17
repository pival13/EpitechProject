/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Kitchen
*/

#pragma once

#include "Pizza.hpp"
#include "Process.hpp"

#include <list>
#include <thread>
#include <condition_variable>

namespace Plazza {
    class Fridge {
        public:
            Fridge(size_t initialSize, size_t refreshTimeout);
            ~Fridge();

            inline bool close() { _closure = true; cvFridgeAccess.notify_all(); }
            void takeIngredient(const std::vector<size_t> &ingredientList);
            void refresh();

            const std::string status() const;

        private:
            bool _closure = false;
            std::condition_variable cvFridgeAccess;
            std::mutex fridgeAccess;
            const std::chrono::milliseconds refreshTimeout;
            std::chrono::time_point<std::chrono::system_clock> lastRefresh;
            std::vector<size_t> ingredients;
            std::thread _refreshThread;
    };

    class Kitchen {
        public:
            enum cookerStatus {
                Waiting,
                TakingOrder,
                TakingIngredients,
                Cooking,
                Delivering
            };

        public:
            Kitchen(size_t nbCooker, size_t refreshTimeout);
            ~Kitchen();

            void addOrder(std::unique_ptr<Pizza> pizza);
            void completeOrder(size_t cookerNb);
            inline size_t getCurrentOrder() const { return (cookerState.size() - std::count(cookerState.begin(), cookerState.end(), cookerStatus::Waiting) + waitingPizzas.size()); }
            void communicater(Process &reception);

        private:
            bool _closure = false;

            std::condition_variable cvEnd;
            std::mutex mWaitingList;
            std::mutex mCompleteList;

            std::vector<cookerStatus> cookerState;
            std::vector<std::unique_ptr<Pizza>> cookersPizza;
            std::vector<std::thread> cooker;

            std::list<std::unique_ptr<Pizza>> waitingPizzas;
            std::list<std::unique_ptr<Pizza>> readyPizzas;
            Fridge fridge;
            std::chrono::time_point<std::chrono::system_clock> lastAction;
    };
};