/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** INetwork
*/

#pragma once

#include <vector>
#include <functional>

class INetwork {
    public:
        virtual ~INetwork() = default;

        virtual void receiveDataCallback(const std::function<void(const std::vector<uint8_t> &, const std::string &, size_t)> &callbackFunction) = 0;
        virtual void sendData(const std::vector<uint8_t> &data, const std::string &ip, size_t port) = 0;
};
