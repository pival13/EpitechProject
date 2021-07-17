/*
** EPITECH PROJECT, 2020
** cpp_d07m_2019 [WSL: Ubuntu]
** File description:
** Admiral
*/

#ifndef ADMIRAL_H
#define ADMIRAL_H

#include "Federation.hpp"

namespace Federation {
    namespace Starfleet {
        class Admiral {
            private:
                const std::string _name;

            public:
                bool (Federation::Starfleet::Ship::*movePtr)(Destination d);
                void (Federation::Starfleet::Ship::*firePtr)(Borg::Ship *target);

                Admiral(std::string name);
                ~Admiral();
                void fire(Federation::Starfleet::Ship *ship, Borg::Ship *target);
                bool move(Federation::Starfleet::Ship *ship, Destination dest);
        };
    };
};

#endif