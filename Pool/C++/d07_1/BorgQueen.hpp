/*
** EPITECH PROJECT, 2020
** cpp_d07m_2019 [WSL: Ubuntu]
** File description:
** BorgQueen
*/

#ifndef BORGQUEEN_H
#define BORGQUEEN_H

#include "Borg.hpp"

namespace Borg {
    class BorgQueen {
        public:
            BorgQueen();
            ~BorgQueen();
            bool (Borg::Ship::*movePtr)(Destination dest);
            void (Borg::Ship::*firePtr)(Federation::Starfleet::Ship *target);
            void (Borg::Ship::*destroyPtr)(Federation::Ship *target);

            bool move(Borg::Ship *ship, Destination dest);
            void fire(Borg::Ship *ship, Federation::Starfleet::Ship *target);
            void destroy(Borg::Ship *ship, Federation::Ship *target);
        protected:
        private:
    };
};

#endif