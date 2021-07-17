/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Reception
*/

#pragma once

#include "Pizza.hpp"

#include <list>
#include <queue>
#include "kitchen/Kitchen.hpp"
#include "Process.hpp"

namespace Plazza {
    class CompletionException : public std::exception {
        public: CompletionException() = default;
        public: inline const char* what() const noexcept { return "End of the day. Good work everyone!"; }
    };

    class Reception {
        public:
            Reception(size_t nbChief, size_t refreshTime);
            ~Reception();

            int newDay();
            void deliverOrders();

        private:
            void parseLine(const std::string &line);
            void parseOrder(const std::smatch &sm);
            void parseOrder(const std::string &line);
            void splitOrders();

            std::list<Process>::iterator getKitchen(size_t index);
            size_t getNbKitchen();
            size_t getKitchenOrder(size_t index);
            void addNewKitchen();
            void addOrder(size_t index, std::unique_ptr<Pizza> &order);

        private:
            bool _end;
            size_t _nbChief;
            size_t _refreshTime;

            std::mutex mWaiter;
            std::thread waiter;

            std::queue<std::unique_ptr<Pizza>> orders;
            std::list<Process> kitchens;
    };
};