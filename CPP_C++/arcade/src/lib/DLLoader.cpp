/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** DLLoader
*/

#include "DirReader.hpp"
#include "DLLoader.hpp"

DLLoader::DLLoader()
: lib(nullptr)
{
}

DLLoader::DLLoader(const std::string &path) noexcept(false)
: lib(nullptr)
{
    load(path);
}

DLLoader::~DLLoader()
{
    if (lib != nullptr)
        dlclose(lib);
}

void DLLoader::load(const std::string &path) noexcept(false)
{
    if (lib != nullptr)
        dlclose(lib);
    lib = dlopen(path.c_str(), RTLD_LAZY);
    if (lib == nullptr)
        throw std::invalid_argument(dlerror());
}