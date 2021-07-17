/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** ComponentInput
*/

#include "Component.hpp"

/******************************/
/*         4008 Adder         */
/******************************/

nts::Component4008::Component4008(const std::string &name)
: AComponent(name, "4008", 16)
{
    size_t pin[4][3] = {{6, 7, 9}, {4, 5, 14}, {2, 3, 14}, {15, 1, 14}};
    _OI[10] = std::vector<size_t>(pin[0], pin[0]+3);
    _OI[11] = std::vector<size_t>(pin[1], pin[1]+3);
    _OI[12] = std::vector<size_t>(pin[2], pin[2]+3);
    _OI[13] = std::vector<size_t>(pin[3], pin[3]+3);
    _OI[14] = std::vector<size_t>(pin[3], pin[3]+3);
}

nts::Tristate nts::Component4008::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));

    size_t output[5] = {10, 11, 12, 13, 14};
    if (std::find(output, output+5, pin) != output+5)
        std::for_each(output, output+4, [&](size_t i) { if (i != pin) _executed[i] = true; });

    AComponent::execute(pin, [&](size_t) {
        for (size_t i = 1; i < _state.size(); i++)
            if (std::find(output, output+5, i) == output+5)
                compute(i);
        for (size_t i : output) {
            if (i == 14)
                continue;
            _state[i] = _state[_OI[i][0]] ^ _state[_OI[i][1]] ^ _state[_OI[i][2]];
            _state[14] = (_state[_OI[i][0]] & _state[_OI[i][1]]) | (_state[_OI[i][0]] & _state[_OI[i][2]]) | (_state[_OI[i][1]] & _state[_OI[i][2]]);
        }
    });
    return _state[pin];
}

/******************************/
/*        4013 D Latch        */
/******************************/
//TODO
nts::Component4013::Component4013(const std::string &name)
: AComponent(name, "4013", 14)
{
    //Clock, data, set, reset
    size_t pin[2][4] = {{3, 5, 6, 4}, {11, 9, 8, 10}};//{6, 3, 5}, {4, 3, 5}, {8, 11, 9}, {10, 11, 9}};
    _OI[1] = std::vector<size_t>(pin[0], pin[0]+4);
    _OI[2] = std::vector<size_t>(pin[0], pin[0]+4);
    _OI[13] = std::vector<size_t>(pin[1], pin[1]+4);
    _OI[12] = std::vector<size_t>(pin[1], pin[1]+4);
}

nts::Tristate nts::Component4013::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));
    AComponent::execute(pin, [&](size_t pin) {
        if (pin < 10) {
            if ((_state[_OI[1][2]] | _state[_OI[1][3]]) == TRUE) {
                _state[1] = _state[_OI[1][2]];
                _state[2] = _state[_OI[1][3]];
            } else {
                _state[1] = (_state[_OI[1][0]] == TRUE && _oldState[_OI[1][0]] == FALSE ? _state[_OI[1][1]] : _state[1]);
                _state[2] = (_state[_OI[1][0]] == TRUE && _oldState[_OI[1][0]] == FALSE ? ~_state[_OI[1][1]] : _state[2]);
            }
        } else {
            if ((_state[_OI[12][2]] | _state[_OI[12][3]]) == TRUE) {
                _state[13] = _state[_OI[12][2]];
                _state[12] = _state[_OI[12][3]];
            } else {
                _state[13] = (_state[_OI[12][0]] == TRUE && _oldState[_OI[12][0]] == FALSE ? _state[_OI[12][1]] : _state[13]);
                _state[12] = (_state[_OI[12][0]] == TRUE && _oldState[_OI[12][0]] == FALSE ? ~_state[_OI[12][1]] : _state[12]);
            }
        }
    });
    return _state[pin];
}

/******************************/
/*        4017 Johnson        */
/******************************/

nts::Component4017::Component4017(const std::string &name)
: AComponent(name, "4017", 15)
{
    size_t pin[3] = {15, 14, 13};
    
    for (size_t i : {3, 2, 4, 7, 10, 1, 5, 6, 9, 11, 12}) {
        _OI[i] = std::vector<size_t>(pin, pin+3);
        _state[i] = FALSE;
    }
    _state[3] = TRUE;
}

nts::Tristate nts::Component4017::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));
    
    size_t output[11] = {3, 2, 4, 7, 10, 1, 5, 6, 9, 11, 12};
    if (std::find(output, output+11, pin) != output+11)
        std::for_each(output, output+11, [&](size_t i) { if (i != pin) _executed[i] = true; });

    AComponent::execute(pin, [&](size_t) {
        Tristate reset = _state[_OI[output[0]][0]];
        bool ok = (_state[_OI[output[0]][1]] == TRUE && _oldState[_OI[output[0]][1]] == FALSE) ||
                  (_state[_OI[output[0]][2]] == TRUE && _oldState[_OI[output[0]][2]] == FALSE);

        if (!ok && reset != TRUE)
            return;
        for (size_t i = 9; i != 0; i--)
            if (reset == TRUE)
                _state[output[i]] = FALSE;
            else if (ok)
                _state[output[i]] = _state[output[i-1]];
            //else
            //    _state[output[i]] = (~(_state[output[i]] | _state[output[i-1]]) == TRUE ? FALSE : UNDEFINED);
        _state[output[0]] = reset | _oldState[output[9]];
        
        size_t pos = std::find_if(output, output+10, [&](size_t i) {return _state[i] == TRUE;}) - output;
        _state[output[10]] = (pos >= 5 && pos <= 9 ? FALSE : TRUE);
    });
    return _state[pin];
}

/******************************/
/*        4040 Counter        */
/******************************/

nts::Component4040::Component4040(const std::string &name)
: AComponent(name, "4040", 16)
{
    size_t pin[2] = {11, 10};
    for (size_t i : {9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1}) {
        _OI[i] = std::vector<size_t>(pin, pin+2);
        _state[i] = FALSE;
    }
}

nts::Tristate nts::Component4040::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));

    size_t output[12] = {9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1};
    if (std::find(output, output+12, pin) != output+12)
        std::for_each(output, output+12, [&](size_t i) { if (i != pin) _executed[i] = true; });

    AComponent::execute(pin, [&](size_t) {
        if (_state[_OI[output[0]][0]] == TRUE) {
            for (size_t pin : output)
                _state[pin] = FALSE;
        //Tristate reset = _state[_OI[output[0]][0]];
        } else if (_state[_OI[output[0]][1]] == FALSE && _oldState[_OI[output[0]][1]] == TRUE) {
            Tristate save = _oldState[_OI[output[0]][1]];
            for (size_t i = 0; i != 12; i++) {
                if (save != FALSE)
                    _state[output[i]] = save ^ (i == 0 ? ~save : _state[output[i-1]]) ^ _state[output[i]];
                save = _oldState[output[i]];
            }
        }
/*
        for (size_t i = 0; i != 12; i++) {
            Tristate tmp = _state[output[i]];
            if (save != FALSE) {
                _state[output[i]] = ~reset & (save ^ (i == 0 ? ~save : _state[output[i-1]]) ^ _state[output[i]]);
            } else
                _state[output[i]] = ~reset & _state[output[i]];
            save = tmp;
        }*/
    });
    return _state[pin];
}

/******************************/
/*         4094 Shift         */
/******************************/

nts::Component4094::Component4094(const std::string &name)
: AComponent(name, "4094", 16)
{
    size_t pin[4] = {3, 1, 2, 15};
    for (size_t i : {4, 5, 6, 7, 14, 13, 12, 11, 9, 10}) {
        _OI[i] = std::vector<size_t>(pin, pin+4);
        _state[i] = FALSE;
    }
}

nts::Tristate nts::Component4094::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));

    size_t output[10] = {4, 5, 6, 7, 14, 13, 12, 11, 9, 10};
    if (std::find(output, output+10, pin) != output+10)
        std::for_each(output, output+10, [&](size_t i) { if (i != pin) _executed[i] = true; });

    AComponent::execute(pin, [&](size_t) {
        Tristate clock = _state[_OI[output[0]][0]];
        bool b = clock == TRUE && _oldState[_OI[output[0]][0]] == FALSE;
        Tristate strobe = _state[_OI[output[0]][1]];

        if (clock == _oldState[_OI[output[0]][0]])
            return;
        if (clock == UNDEFINED) {
            _state[output[8]] = UNDEFINED;
            _state[output[9]] = UNDEFINED;
        } else
            _state[output[b ? 8 : 9]] = _state[output[6]];
        for (size_t i = 8; i != 0; i--) {
            if (strobe == TRUE && b)
                _state[output[i-1]] = (i == 1 ? _state[_OI[output[i]][2]] : _state[output[i-2]]);
            //else if ((clock & strobe) != FALSE)
            //    _state[output[i-1]] = ((_state[output[i-1]] ^ (i == 1 ? _state[_OI[output[i]][2]] : _state[output[i-2]])) == FALSE ? _state[output[i-1]] : UNDEFINED);
        }
    });
    return (_state[15] == TRUE || pin == 9 || pin == 10 ? _state[pin] : UNDEFINED);
}

/******************************/
/*        4514 Decoder        */
/******************************/

nts::Component4514::Component4514(const std::string &name)
: AComponent(name, "4514", 24)
{
    size_t pin[6] = {1, 23, 2, 3, 21, 22};

    for (size_t i : {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15}) {
        _OI[i] = std::vector<size_t>(pin, pin+6);
        _state[i] = FALSE;
    }
}

nts::Tristate nts::Component4514::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));

    size_t output[16] = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};
    if (std::find(output, output+16, pin) != output+16)
        std::for_each(output, output+16, [&](size_t i) { if (i != pin) _executed[i] = true; });
    AComponent::execute(pin, [&](size_t) {
        Tristate strobe = _state[_OI[output[0]][0]];
        Tristate inhibit = _state[_OI[output[0]][1]];

        if (strobe == FALSE)
            return;
        if (inhibit == TRUE) {
            for (size_t s : output)
                _state[s] = (~strobe) & _state[s];
            return;
        }

        Tristate data[4] = {_state[_OI[output[0]][2]], _state[_OI[output[0]][3]], _state[_OI[output[0]][4]], _state[_OI[output[0]][5]]};
        for (size_t i = 0; i != 14; i++) {
            Tristate nb[4] = {(i & 1 ? TRUE : FALSE), (i & 2 ? TRUE : FALSE), (i & 4 ? TRUE : FALSE), (i & 8 ? TRUE : FALSE)};
            _state[output[i]] = _state[output[i]] | (
                (~nb[0] ^ data[0]) & (~nb[1] ^ data[1]) & (~nb[2] ^ data[2]) & (~nb[3] ^ data[3])
            );
        }
    });
    return _state[pin];
}

/******************************/
/*            4801            */
/******************************/
/*TODO
nts::Component4801::Component4801(const std::string &name)
: AComponent(name, "4801", 14)
{
    size_t pin[4][2] = {{1, 2}, {5, 6}, {8, 9}, {12, 13}};
    _OI[3] = std::vector<size_t>(pin[0], pin[0]+2);
    _OI[4] = std::vector<size_t>(pin[1], pin[1]+2);
    _OI[10] = std::vector<size_t>(pin[2], pin[2]+2);
    _OI[11] = std::vector<size_t>(pin[3], pin[3]+2);
}

nts::Tristate nts::Component4801::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));
    AComponent::execute(pin, [&](size_t pin) {
        _state[pin] = _state[_OI[pin][0]] ^ _state[_OI[pin][1]];
    });
    return _state[pin];
}*/

/******************************/
/*            2716            */
/******************************/
/*TODO
nts::Component2716::Component2716(const std::string &name)
: AComponent(name, "2716", 14)
{
    size_t pin[4][2] = {{1, 2}, {5, 6}, {8, 9}, {12, 13}};
    _OI[3] = std::vector<size_t>(pin[0], pin[0]+2);
    _OI[4] = std::vector<size_t>(pin[1], pin[1]+2);
    _OI[10] = std::vector<size_t>(pin[2], pin[2]+2);
    _OI[11] = std::vector<size_t>(pin[3], pin[3]+2);
}

nts::Tristate nts::Component2716::compute(std::size_t pin)
{
    if (pin >= _state.size() || pin == 0)
        throw my_except("Unknow pin " + std::to_string(pin));
    AComponent::execute(pin, [&](size_t pin) {
        _state[pin] = _state[_OI[pin][0]] ^ _state[_OI[pin][1]];
    });
    return _state[pin];
}*/

/*
simulate
display
*/