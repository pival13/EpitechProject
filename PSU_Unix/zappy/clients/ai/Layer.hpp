/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Layer
*/

#pragma once

#include "Trantorian.hpp"

class Layer : public Trantorian {
    public:
        Layer(const std::string &teamName);
        ~Layer() = default;

        void launch();

    protected:
        void actionCallback(FunctionsCode funct, bool result);
        void lookCallback(const std::deque<inv_t> &content);
        void inventoryCallback(const inv_t &/*inventory*/) {}
        void messageReceived(Direction orig, const std::string &msg);
        void beenEject(Direction /*orig*/) {}
        void isDead() {}
        void inIncantation() {}
        void remainingPlace(size_t remainingPlaces);

    private:
        void layerCreateChild();
        void checkDeadPlayer();
        void checkMissingTrantorian();
        void prepareNewConnection();

        bool _alreadyTalk = false;
        int _missingTrantorian;
        int _reservedPlace = 0;
        std::map<size_t, size_t> _lastTalk;

        std::list<std::string> _childsList;
        std::mutex _listMutex;
};
