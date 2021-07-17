/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** AComponent
*/

#pragma once

#include "IComponent.hpp"
#include "../my_except.hpp"
#include <functional>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <utility>

namespace nts {
    class ComponentPin {
        public:
            ComponentPin(IComponent &comp, size_t pinNb);
            ~ComponentPin();

            ComponentPin &operator=(const ComponentPin&);

            IComponent &component;
            size_t pin;
    };

    class AComponent : public IComponent {
        public:
            AComponent(const std::string &name, const std::string &type, size_t pinNb);
            ~AComponent();

            virtual void setLink(size_t pin, nts::IComponent &other, size_t other_pin);
            void dump() const;
            virtual bool isLinked() const;

            void reset();
            const std::string &getType() const;
            const std::string &getName() const;

        protected:
            void execute(size_t, std::function<void(size_t)> f);

            std::vector<Tristate> _state;
            std::vector<Tristate> _oldState;
            std::vector<bool> _executed;
            std::map<size_t, ComponentPin> _linkedPin;
            std::map<size_t, std::vector<size_t>> _OI;

            const std::string name;
            const std::string type;
    };

    /// [_)
    Tristate operator&(Tristate, Tristate);
    /// )_)
    Tristate operator|(Tristate, Tristate);
    /// ))_)
    Tristate operator^(Tristate, Tristate);
    /// °
    Tristate operator~(Tristate);
}
std::ostream &operator<<(std::ostream &, nts::Tristate);