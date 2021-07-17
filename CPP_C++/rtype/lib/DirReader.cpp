/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** DirReader
*/

#include "DirReader.hpp"

DirReader::DirReader()
: _path(), _files()
{
}

DirReader::DirReader(const std::string &path)
: DirReader()
{
    load(path);
}

DirReader::~DirReader() {}

void DirReader::load(const std::string &path)
{
    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path))
        throw std::invalid_argument("The given path \""+path+"\" does not exist or is not a directory.");
    _path = std::filesystem::absolute(path);
    refresh();
}

void DirReader::refresh()
{
    _files.clear();

    for (const auto &entry : std::filesystem::directory_iterator(_path))
        _files.push_back(entry);
}

std::string DirReader::getPath() const { return std::filesystem::path(_path).lexically_normal().string(); }

std::vector<std::string> DirReader::getAll(const std::string &re) const
{
    std::vector<std::string> vect(_files.size());

    size_t i = 0;
    for (const auto &f : _files)
        if (f.exists() && std::regex_match(f.path().string(), std::regex(re))) {
            vect[i] = f.path().string();
            ++i;
        }
    vect.resize(i);
    return vect;
}

std::vector<std::string> DirReader::getFiles(const std::string &re) const
{
    std::vector<std::string> vect(_files.size());

    size_t i = 0;
    for (const auto &f : _files)
        if (f.exists() && f.is_regular_file() && std::regex_match(f.path().string(), std::regex(re))) {
            vect[i] = f.path().string();
            ++i;
        }
    vect.resize(i);
    return vect;
}

std::vector<std::string> DirReader::getDirectories(const std::string &re) const
{
    std::vector<std::string> vect(_files.size());

    size_t i = 0;
    for (const auto &f : _files)
        if (f.exists() && f.is_directory() && std::regex_match(f.path().string(), std::regex(re))) {
            vect[i] = f.path().string();
            ++i;
        }
    vect.resize(i);
    return vect;
}