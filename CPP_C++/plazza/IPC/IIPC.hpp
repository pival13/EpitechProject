/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** IPC
*/

#pragma once

#include <string>
#include "IPObject.hpp"

class IIPC {
    public:
        ~IIPC() = default;

        virtual void prepareFirstSide() = 0;
        virtual void prepareOtherSide() = 0;

        virtual bool isActive() const = 0;

        virtual ssize_t exportData(const IPData &data) = 0;

        virtual IPData importData() = 0;
};
