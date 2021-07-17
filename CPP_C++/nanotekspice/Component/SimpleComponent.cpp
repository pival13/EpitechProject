/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** ComponentInput
*/

#include "Component.hpp"

/******************************/
/*           Input            */
/******************************/

nts::ComponentInput::ComponentInput(const std::string &name) : AComponent(name, "Input", 1) {}

void nts::ComponentInput::setState(Tristate state) { _state[1] = state; }

nts::Tristate nts::ComponentInput::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::UNDEFINED;
    return _state[pin];
}

/******************************/
/*          Output            */
/******************************/

nts::ComponentOutput::ComponentOutput(const std::string &name) : AComponent(name, "Output", 1) {}

nts::Tristate nts::ComponentOutput::compute(size_t pin)
{
    if (!_linkedPin.count(pin))
        _state[pin] = nts::UNDEFINED;
    else
        _state[pin] = _linkedPin.at(pin).component.compute(_linkedPin.at(pin).pin);
    return _state[pin];
}

std::ostream &operator<<(std::ostream &os, nts::ComponentOutput &c)
{
    os << c.getName() << "=" << c.compute();
    return os;
}

/******************************/
/*           Clock            */
/******************************/

nts::ComponentClock::ComponentClock(const std::string &name) : AComponent(name, "Clock", 1), ComponentInput(name) {}

nts::Tristate nts::ComponentClock::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::UNDEFINED;
    if (_executed[pin])
        return ~_state[pin];
    _state[pin] = ~_state[pin];
    _executed[pin] = true;
    return ~_state[pin];
}

/******************************/
/*           True             */
/******************************/

nts::ComponentTrue::ComponentTrue(const std::string &name) : AComponent(name, "True", 1) { _state[1] = nts::TRUE; }

nts::Tristate nts::ComponentTrue::compute(std::size_t) { return nts::TRUE; }

/******************************/
/*           False            */
/******************************/

nts::ComponentFalse::ComponentFalse(const std::string &name) : AComponent(name, "False", 1) { _state[1] = nts::FALSE; }

nts::Tristate nts::ComponentFalse::compute(std::size_t) { return nts::FALSE; }