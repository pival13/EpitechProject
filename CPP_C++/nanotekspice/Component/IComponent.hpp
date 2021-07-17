/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** IComponent
*/

#pragma once

#include <cstddef>
#include <iostream>

namespace nts {
    enum Tristate {
        UNCALCULATE = -2,
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false
    };

    class IComponent {
        public:
            virtual ~IComponent() = default;

            virtual nts::Tristate compute(std::size_t pin=1) = 0;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t other_pin) = 0;
            virtual void dump() const = 0;
            virtual void reset() = 0;

            virtual bool isLinked() const = 0;
            virtual const std::string &getName() const = 0;
            virtual const std::string &getType() const = 0;
    };
}