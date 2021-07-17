/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** ModuleMemory
*/

#include "ModuleMemory.hpp"

ModuleMemory::ModuleMemory()
: AModuleSixtyTime("Memory", "/proc/meminfo")
{
    update();
}

ModuleMemory::~ModuleMemory()
{
}

void ModuleMemory::update()
{
    std::ifstream _file(_filepath);
    if (!_file.is_open())
        return;

    _file.seekg(0);
    std::regex re[6] = {std::regex("(MemTotal):\\s*([0-9]*) kB"), 
                        std::regex("(MemFree):\\s*([0-9]*) kB"), 
                        std::regex("(Buffers):\\s*([0-9]*) kB"), 
                        std::regex("(Cached):\\s*([0-9]*) kB"),
                        std::regex("(SwapTotal):\\s*([0-9]*) kB"), 
                        std::regex("(SwapFree):\\s*([0-9]*) kB")};
    updateMap(_file, _info, std::vector<std::regex>(re, re+6));
    _file.close();
}