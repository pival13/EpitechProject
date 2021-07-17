/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** ISSystem
*/

#pragma once

#include "Component/IComponent.hpp"
#include <memory>
#include <vector>

namespace nts {
    class ISystem {
        public:
            virtual ~ISystem() = default;

            virtual void display() const = 0;
            virtual void simulate() = 0;
            virtual void dump() const = 0;
            virtual void loop() = 0;
            virtual void assign(const std::string &name, const std::string &state, bool init_assign) = 0;
            virtual std::unique_ptr<IComponent> createComponent(const std::string &type, const std::string &value) = 0;

        protected:
        private:
    };
}