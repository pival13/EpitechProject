/*
** EPITECH PROJECT, 2020
** cpp_d07m_2019 [WSL: Ubuntu]
** File description:
** Borg
*/

#ifndef BORG_H
#define BORG_H

#include "WarpSystem.hpp"

namespace Federation {
    namespace Starfleet {
        class Ship;
    };
    class Ship;
};

namespace Borg {
	class Ship {
        private:
            const int _side;
            const short _maxWarp;
            const Destination _home;
            Destination _location;
            WarpSystem::Core *_core;
            int _shield;
            int _weaponFrequency;
            short _repair;

        public:
            Ship(int weaponFrequency=20, short repair=3);
            ~Ship();
            void setupCore(WarpSystem::Core *core);
            void checkCore();
            int getShield();
            void setShield(int shield);
            int getWeaponFrequency();
            void setWeaponFrequency(int frequency);
            short getRepair();
            void setRepair(short repair);
            bool move(int warp, Destination d);
            bool move(int warp);
            bool move(Destination d);
            bool move();
            void fire(Federation::Starfleet::Ship *target);
            void fire(Federation::Ship *target);
            void repair();
    };
};

#endif