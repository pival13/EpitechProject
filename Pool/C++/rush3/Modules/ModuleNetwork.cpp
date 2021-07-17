/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** ModuleNetwork
*/

#include "ModuleNetwork.hpp"

ModuleNetwork::ModuleNetwork()
: AModuleSixtyTime("Network", "/proc/net/dev")
{
    update();
}

ModuleNetwork::~ModuleNetwork()
{
}

void ModuleNetwork::update()
{
    std::ifstream in(_filepath);
    if (!in.is_open())
        return;

    std::smatch rmatch;
    std::string content;

    std::getline(in, content, '\n');
    _info["Type"].push_front("");
    _info["Input"].push_front("-1");
    _info["Output"].push_front("-1");
    while (!in.eof()) {
        if (std::regex_match(content, rmatch, std::regex("\\s*([^:]*):\\s*([0-9]*)\\s*[0-9]*\\s*[0-9]*\\s*[0-9]*\\s*[0-9]*\\s*[0-9]*\\s*[0-9]*\\s*[0-9]*\\s*([0-9]*)\\s*[0-9]*\\s*[0-9]*\\s*[0-9]*\\s*[0-9]*\\s*[0-9]*\\s*[0-9]*\\s*[0-9]*")))
            if (stoi(rmatch[2].str()) > stoi(_info["Input"].front()) && stoi(rmatch[3].str()) > stoi(_info["Output"].front())) {
                _info["Type"].front() = rmatch[1].str();
                _info["Input"].front() = rmatch[2].str();
                _info["Output"].front() = rmatch[3].str();
            }
        std::getline(in, content, '\n');
    }
    if (_info["Type"].size() > 60) {
        _info["Type"].pop_back();
        _info["Input"].pop_back();
        _info["Output"].pop_back();
    }
    in.close();
}