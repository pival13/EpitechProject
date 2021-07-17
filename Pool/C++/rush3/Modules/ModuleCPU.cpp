/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** ModuleCPU
*/

#include "ModuleCPU.hpp"

ModuleCPU::ModuleCPU()
: AModuleSixtyTime("CPU", "/proc/cpuinfo")
{
    initialUpdate();
}

ModuleCPU::~ModuleCPU()
{
}

void ModuleCPU::initialUpdate()
{
    std::ifstream _file(_filepath);
    if (!_file.is_open())
        return;

    _file.seekg(0);
    std::regex re[2] = {std::regex("(cpu cores)\\s*: ([0-9]*.[0-9]*)"),
                        std::regex("(model name)\\s*: (.*)")};
    updateMap(_file, _info, std::vector<std::regex>(re, re+2));

    std::ifstream in("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq");

    if (!in.is_open())
        return;
    std::string s;
    std::getline(in, s, '\0');
    _info["MaxFreq"].push_front(s);
    if (_info["MaxFreq"].size() > 60)
        _info["MaxFreq"].pop_back();
    in.close();
    _file.close();

    update();
}

void ModuleCPU::update()
{
    std::ifstream _file(_filepath);
    if (!_file.is_open())
        return;

    _file.seekg(0);
    std::smatch rmatch;
    std::string content;

    std::getline(_file, content, '\n');
    for (int i = 0; !_file.eof();) {
        if (std::regex_match(content, rmatch, std::regex("cpu MHz\\s*: (.*)"))) {
            _info["CPU " + std::to_string(i)].push_front(rmatch[1].str());
            if (_info["CPU " + std::to_string(i)].size() > 60)
                _info["CPU " + std::to_string(i)].pop_back();
            i++;
        }
        std::getline(_file, content, '\n');
    }
    _file.close();
}