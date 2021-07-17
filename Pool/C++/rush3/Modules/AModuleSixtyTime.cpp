/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** AModuleSixtyTime
*/

#include "AModuleSixtyTime.hpp"

AModuleSixtyTime::AModuleSixtyTime(const std::string &name, const std::string &filepath)
: _name(name), _isActive(true), _filepath(filepath), _info()
{
}

AModuleSixtyTime::~AModuleSixtyTime()
{
}

const std::string &AModuleSixtyTime::getName() const { return _name; }
bool AModuleSixtyTime::getStatus() const { return _isActive; }
bool AModuleSixtyTime::isDrawable() const { return true; }
oneTimeInfo AModuleSixtyTime::getOneInfo() const { return oneTimeInfo(); }
sixtyTimeInfo AModuleSixtyTime::getSixtyInfo() const { return _info; }
void AModuleSixtyTime::setStatus(bool status) { _isActive = status; }

void AModuleSixtyTime::updateMap(std::ifstream &in, std::map<std::string, std::list<std::string>> &map, const std::vector<std::regex> &pattern)
{
    std::smatch rmatch;
    std::string content;

    std::getline(in, content, '\n');
    while (content.size() > 1 && !in.eof()) {
        for (size_t i = 0; i != pattern.size(); i++)
            if (std::regex_match(content, rmatch, pattern[i])) {
                map[rmatch[1].str()].push_front(rmatch[2].str());
                if (map[rmatch[1].str()].size() > 60)
                    map[rmatch[1].str()].pop_back();
            }
        std::getline(in, content, '\n');
    }
}