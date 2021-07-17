/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** DomesticKoala
*/

#include "DomesticKoala.hpp"

DomesticKoala::DomesticKoala(KoalaAction &ka)
: _ka(ka), _char(), _action(new std::vector<methodPointer_t>)
{
}

DomesticKoala::DomesticKoala(const DomesticKoala &koala)
: _char(), _action(new std::vector<methodPointer_t>)
{
    *this = koala;
}

DomesticKoala::~DomesticKoala()
{
    delete _action;
}

DomesticKoala &DomesticKoala::operator=(const DomesticKoala &koala)
{
    _ka = koala.getKoalaAction();
    _action->clear();
    _char.clear();
    for (size_t i = 0; i != koala.getCommand().size(); i++) {
        _char.push_back(koala.getCommand().at(i));
        _action->push_back(koala.getAction()->at(i));
    }
    return *this;
}

const std::vector<DomesticKoala::methodPointer_t> *DomesticKoala::getAction() const { return _action; }
const std::vector<unsigned char> &DomesticKoala::getCommand() const { return _char; }
const KoalaAction &DomesticKoala::getKoalaAction() const { return _ka; }

void DomesticKoala::setKoalaAction(KoalaAction &ka)
{
    _ka = ka;
    _char.clear();
    _action->clear();
}

void DomesticKoala::learnAction(unsigned char command, methodPointer_t action)
{
    for (size_t i = 0; i != _char.size(); i++)
        if (_char[i] == command) {
            _action->at(i) = action;
            return;
        }
    _char.push_back(command);
    _action->push_back(action);
}

void DomesticKoala::unlearnAction(unsigned char command)
{
    auto itAct = _action->begin();

    for (auto it = _char.begin(); it != _char.end(); ++it, ++itAct)
        if (*it == command) {
            _char.erase(it);
            _action->erase(itAct);
        }
}

void DomesticKoala::doAction(unsigned char command, const std::string &param)
{
    for (size_t i = 0; i != _char.size(); i++)
        if (_char[i] == command) {
            methodPointer_t f = _action->at(i);
            (_ka.*f)(param);
        }
}