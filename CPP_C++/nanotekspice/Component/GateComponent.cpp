/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** ComponentInput
*/

#include "Component.hpp"

/******************************/
/*            4001            */
/******************************/

nts::Component4001::Component4001(const std::string &name)
: AComponent(name, "4001", 14)
{
    size_t pin[4][2] = {{1, 2}, {5, 6}, {8, 9}, {12, 13}};
    _OI[3] = std::vector<size_t>(pin[0], pin[0]+2);
    _OI[4] = std::vector<size_t>(pin[1], pin[1]+2);
    _OI[10] = std::vector<size_t>(pin[2], pin[2]+2);
    _OI[11] = std::vector<size_t>(pin[3], pin[3]+2);
}

nts::Tristate nts::Component4001::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));
    AComponent::execute(pin, [this](size_t pin) {
        _state[pin] = ~(_state[_OI[pin][0]] | _state[_OI[pin][1]]);
    });
    return _state[pin];
}

/******************************/
/*            4011            */
/******************************/

nts::Component4011::Component4011(const std::string &name)
: AComponent(name, "4011", 14)
{
    size_t pin[4][2] = {{1, 2}, {5, 6}, {8, 9}, {12, 13}};
    _OI[3] = std::vector<size_t>(pin[0], pin[0]+2);
    _OI[4] = std::vector<size_t>(pin[1], pin[1]+2);
    _OI[10] = std::vector<size_t>(pin[2], pin[2]+2);
    _OI[11] = std::vector<size_t>(pin[3], pin[3]+2);
}

nts::Tristate nts::Component4011::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));
    AComponent::execute(pin, [&](size_t pin) {
        _state[pin] = ~(_state[_OI[pin][0]] & _state[_OI[pin][1]]);
    });
    return _state[pin];
}

/******************************/
/*            4030            */
/******************************/

nts::Component4030::Component4030(const std::string &name)
: AComponent(name, "4030", 14)
{
    size_t pin[4][2] = {{1, 2}, {5, 6}, {8, 9}, {12, 13}};
    _OI[3] = std::vector<size_t>(pin[0], pin[0]+2);
    _OI[4] = std::vector<size_t>(pin[1], pin[1]+2);
    _OI[10] = std::vector<size_t>(pin[2], pin[2]+2);
    _OI[11] = std::vector<size_t>(pin[3], pin[3]+2);
}

nts::Tristate nts::Component4030::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));

    AComponent::execute(pin, [&](size_t pin) {
        _state[pin] = _state[_OI[pin][0]] ^ _state[_OI[pin][1]];
    });
    return _state[pin];
}

/******************************/
/*            4069            */
/******************************/

nts::Component4069::Component4069(const std::string &name)
: AComponent(name, "4069", 14)
{
    size_t pin[6][1] = {{1}, {3}, {5}, {9}, {11}, {13}};
    _OI[2] = std::vector<size_t>(pin[0], pin[0]+1);
    _OI[4] = std::vector<size_t>(pin[1], pin[1]+1);
    _OI[6] = std::vector<size_t>(pin[2], pin[2]+1);
    _OI[8] = std::vector<size_t>(pin[3], pin[3]+1);
    _OI[10] = std::vector<size_t>(pin[4], pin[4]+1);
    _OI[12] = std::vector<size_t>(pin[5], pin[5]+1);
}

nts::Tristate nts::Component4069::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));
    AComponent::execute(pin, [&](size_t pin) {
        _state[pin] = ~_state[_OI[pin][0]];
    });
    return _state[pin];
}

/******************************/
/*            4071            */
/******************************/

nts::Component4071::Component4071(const std::string &name)
: AComponent(name, "4071", 14)
{
    size_t pin[4][2] = {{1, 2}, {5, 6}, {8, 9}, {12, 13}};
    _OI[3] = std::vector<size_t>(pin[0], pin[0]+2);
    _OI[4] = std::vector<size_t>(pin[1], pin[1]+2);
    _OI[10] = std::vector<size_t>(pin[2], pin[2]+2);
    _OI[11] = std::vector<size_t>(pin[3], pin[3]+2);
}

nts::Tristate nts::Component4071::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));
    AComponent::execute(pin, [&](size_t pin) {
        _state[pin] = _state[_OI[pin][0]] | _state[_OI[pin][1]];
    });
    return _state[pin];
}

/******************************/
/*            4081           */
/******************************/

nts::Component4081::Component4081(const std::string &name)
: AComponent(name, "4081", 14)
{
    size_t pin[4][2] = {{1, 2}, {5, 6}, {8, 9}, {12, 13}};
    _OI[3] = std::vector<size_t>(pin[0], pin[0]+2);
    _OI[4] = std::vector<size_t>(pin[1], pin[1]+2);
    _OI[10] = std::vector<size_t>(pin[2], pin[2]+2);
    _OI[11] = std::vector<size_t>(pin[3], pin[3]+2);
}

nts::Tristate nts::Component4081::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));
    AComponent::execute(pin, [&](size_t pin) {
        _state[pin] = _state[_OI[pin][0]] & _state[_OI[pin][1]];
    });
    return _state[pin];
}
