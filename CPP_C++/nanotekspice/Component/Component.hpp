/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** Component4001
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class ComponentInput : virtual public AComponent {
        public:
            ComponentInput(const std::string &name);
            ~ComponentInput() = default;

            virtual nts::Tristate compute(std::size_t pin=1);
            void setState(nts::Tristate);
    };

    class ComponentOutput : public AComponent {
        public:
            ComponentOutput(const std::string &name);
            ~ComponentOutput() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class ComponentClock : public ComponentInput {
        public:
            ComponentClock(const std::string &name);
            ~ComponentClock() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class ComponentTrue : public AComponent {
        public:
            ComponentTrue(const std::string &name);
            ~ComponentTrue() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class ComponentFalse : public AComponent {
        public:
            ComponentFalse(const std::string &name);
            ~ComponentFalse() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4001 : public AComponent {
        public:
            Component4001(const std::string &name);
            ~Component4001() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4008 : public AComponent {
        public:
            Component4008(const std::string &name);
            ~Component4008() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4011 : public AComponent {
        public:
            Component4011(const std::string &name);
            ~Component4011() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4013 : public AComponent {
        public:
            Component4013(const std::string &name);
            ~Component4013() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4017 : public AComponent {
        public:
            Component4017(const std::string &name);
            ~Component4017() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4030 : public AComponent {
        public:
            Component4030(const std::string &name);
            ~Component4030() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4040 : public AComponent {
        public:
            Component4040(const std::string &name);
            ~Component4040() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4069 : public AComponent {
        public:
            Component4069(const std::string &name);
            ~Component4069() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4071 : public AComponent {
        public:
            Component4071(const std::string &name);
            ~Component4071() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4081 : public AComponent {
        public:
            Component4081(const std::string &name);
            ~Component4081() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4094 : public AComponent {
        public:
            Component4094(const std::string &name);
            ~Component4094() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component4514 : public AComponent {
        public:
            Component4514(const std::string &name);
            ~Component4514() = default;

            nts::Tristate compute(std::size_t pin=1);
    };
/*TODO
    class Component4801 : public AComponent {
        public:
            Component4801(const std::string &name);
            ~Component4801() = default;

            nts::Tristate compute(std::size_t pin=1);
    };

    class Component2716 : public AComponent {
        public:
            Component2716(const std::string &name);
            ~Component2716() = default;

            nts::Tristate compute(std::size_t pin=1);
    };*/

    //4503 4512 i4004
}

std::ostream &operator<<(std::ostream &os, nts::ComponentOutput &c);