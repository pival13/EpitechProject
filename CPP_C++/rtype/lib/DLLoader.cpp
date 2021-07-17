/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** DLLoader
*/

#include "DirReader.hpp"
#include "DLLoader.hpp"

DLLoader::DLLoader()
: lib(nullptr), libName()
{
}

DLLoader::DLLoader(const std::string &libraryName)
: lib(nullptr)
{
    load(".", libraryName);
}

DLLoader::DLLoader(const std::string &path, const std::string &libraryName)
: lib(nullptr)
{
    load(path, libraryName);
}

DLLoader::DLLoader(const DLLoader &other)
: lib(nullptr), libName(other.libName)
{
    if (!libName.empty())
        _load(libName);
}

DLLoader &DLLoader::operator=(const DLLoader &other)
{
    libName = other.libName;
    if (!libName.empty())
        _load(libName);
    else if (lib) {
        DLL_FREE(lib);
        lib = nullptr;
    }
    return *this;
}

DLLoader::~DLLoader()
{
    if (lib != nullptr)
        DLL_FREE(lib);
    lib = nullptr;
}

void DLLoader::load(const std::string &path, const std::string &libraryName)
{
    libName = DLL_NAME(path, libraryName);
    _load(libName);    
}

void DLLoader::_load(const std::string &_lib)
{
    if (lib != nullptr)
        DLL_FREE(lib);
    lib = DLL_CREATE(_lib.c_str());
    if (lib == nullptr)
        throw std::invalid_argument("Failed to load library \""+libName+"\"");
}

DLLoader::operator bool() const
{
    return lib != nullptr;
}
