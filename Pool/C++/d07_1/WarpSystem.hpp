/*
** EPITECH PROJECT, 2020
** cpp_d07m_2019 [WSL: Ubuntu]
** File description:
** WarpSystem
*/

#ifndef WARPSYSTEM_H
#define WARPSYSTEM_H

#include <iostream>
#include "Destination.hpp"

namespace WarpSystem {
	class QuantumReactor {
        private:
            bool _stability;

        public:
            QuantumReactor(/* args */);
            ~QuantumReactor();
            bool isStable();
            void setStability(bool stability);
    };

    class Core {
        private:
            QuantumReactor *_coreReactor;
        public:
            Core(QuantumReactor *reactor);
            ~Core();
            QuantumReactor *checkReactor();
    };    
};

#endif