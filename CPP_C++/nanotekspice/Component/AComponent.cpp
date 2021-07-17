/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** AComponent
*/

#include "AComponent.hpp"

namespace nts { class ComponentInput : public AComponent {}; };

/*******************************/
/*        ComponentPin         */
/*******************************/

nts::ComponentPin::ComponentPin(IComponent &comp, size_t pinNb)
: component(comp), pin(pinNb)
{
}

nts::ComponentPin::~ComponentPin()
{
}

nts::ComponentPin &nts::ComponentPin::operator=(const ComponentPin &other)
{
    component = other.component;
    pin = other.pin;
    return *this;
}

/*******************************/
/*          AComponent         */
/*******************************/

nts::AComponent::AComponent(const std::string &name, const std::string &type, size_t pinNb)
: _state(pinNb+1, UNDEFINED), _oldState(pinNb+1, UNDEFINED), _executed(pinNb+1, false), name(name), type(type)
{
}

nts::AComponent::~AComponent()
{
}

const std::string &nts::AComponent::getType() const { return type; }
const std::string &nts::AComponent::getName() const { return name; }

void nts::AComponent::reset()
{
    for (size_t i = 0; i != _executed.size(); i++)
        _executed[i] = false;
    for (size_t i = 0; i != _state.size(); i++)
        _oldState[i] = _state[i];
}

void nts::AComponent::execute(size_t pin, std::function<void(size_t)> f)
{
    if (_executed[pin])
        return;
    _executed[pin] = true;
    if (_OI.count(pin)) {
        for (size_t otherPin : _OI[pin])
            compute(otherPin);
        f(pin);
    } else {
        if (_linkedPin.count(pin))
            _state[pin] = _linkedPin.at(pin).component.compute(_linkedPin.at(pin).pin);
        else
            _state[pin] = nts::UNDEFINED;
    }
}

void nts::AComponent::setLink(size_t pin, nts::IComponent &other, size_t other_pin)
{
    static int done = 0;

    if (pin >= _state.size() || pin == 0)
        throw my_except("Pin " + std::to_string(pin) + " unknow on component " + type + " \"" + name + "\"");
    if (done < 2) {
        done++;
        _linkedPin.insert(std::pair<size_t, ComponentPin>(pin, ComponentPin(other, other_pin)));
        other.setLink(other_pin, *this, pin);
    }
    done = 0;
}

void nts::AComponent::dump() const
{
    std::cout << type << " \"" << name << "\":" << std::endl;
    for (size_t pin = 1; pin <= _state.size() -1; pin++) {
        std::cout << "  pin " << pin;
        if (_OI.count(pin)) {
            std::cout << " {";
            for (auto i : _OI.at(pin))
                std::cout << i << ", ";
            std::cout << "\b\b}";
        }
        if (_linkedPin.count(pin))
            std::cout << " (" << _linkedPin.at(pin).component.getName() << "." << _linkedPin.at(pin).pin << ")";
        std::cout << " => " << _state[pin] << std::endl;
    }
}

bool nts::AComponent::isLinked() const
{
    return _linkedPin.size() != 0;
}

/*******************************/
/*          Tristate           */
/*******************************/

/// [_)
nts::Tristate nts::operator&(nts::Tristate a, nts::Tristate b)
{
    if (a == nts::FALSE || b == nts::FALSE)
        return nts::FALSE;
    if (a == nts::TRUE && a == b)
        return nts::TRUE;
    return nts::UNDEFINED;
}

/// )_)
nts::Tristate nts::operator|(nts::Tristate a, nts::Tristate b)
{
    if (a == nts::TRUE || b == nts::TRUE)
        return nts::TRUE;
    if (a == nts::FALSE && a == b)
        return nts::FALSE;
    return nts::UNDEFINED;
}

/// ))_)
nts::Tristate nts::operator^(nts::Tristate a, nts::Tristate b)
{
    if (a == nts::UNDEFINED || b == nts::UNDEFINED)
        return nts::UNDEFINED;
    if (a == b)
        return nts::FALSE;
    return nts::TRUE;
}

nts::Tristate nts::operator~(nts::Tristate a)
{
    if (a == nts::TRUE)
        return nts::FALSE;
    if (a == nts::FALSE)
        return nts::TRUE;
    return nts::UNDEFINED;
}

std::ostream &operator<<(std::ostream &os, nts::Tristate state)
{
    os << (state == nts::UNDEFINED ? "U" : (state == nts::TRUE ? "1" : "0"));
    return os;
}