/*
** EPITECH PROJECT, 2020
** cpp_d07m_2019 [WSL: Ubuntu]
** File description:
** Federation
*/

#ifndef FEDERATION_H
#define FEDERATION_H

#include "WarpSystem.hpp"

namespace Borg {
    class Ship;
}

namespace Federation {
	namespace Starfleet {
        class Captain {
            private:
                const std::string _name;
                int _age;

            public:
                Captain(std::string name);
                ~Captain();
                std::string getName();
                int getAge();
                void setAge(int age);
        };

        class Ensign {
            private:
                std::string _name;

            public:
                explicit Ensign(std::string name);
                ~Ensign();
        };

        class Ship {
            private:
                const int _length;
                const int _width;
                const std::string _name;
                const short _maxWarp;
                const Destination _home;
                Destination _location;
                WarpSystem::Core *_core;
                int _shield;
                int _photonTorpedo;
                Captain *_captain;

            public:
                Ship();
                Ship(int length, int width, std::string name, short maxWarp, int torpedo=0);
                ~Ship();
                void setupCore(WarpSystem::Core *core);
                void checkCore();
                void promote(Captain *captain);
                bool move(int warp, Destination d);
                bool move(int warp);
                bool move(Destination d);
                bool move();
                int getShield();
                void setShield(int shield);
                int getTorpedo();
                void setTorpedo(int torpedo);
                void fire(Borg::Ship *target);
                void fire(int torpedo, Borg::Ship *target);
        };
    };

    class Ship {
        private:
            const int _length;
            const int _width;
            const std::string _name;
            const short _maxWarp;
            const Destination _home;
            Destination _location;
            WarpSystem::Core *_core;

        public:
            Ship(int length, int width, std::string name);
            ~Ship();
            void setupCore(WarpSystem::Core *core);
            void checkCore();
            WarpSystem::Core *getCore();
            bool move(int warp, Destination d);
            bool move(int warp);
            bool move(Destination d);
            bool move();
    };
};

#endif