/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** DirReader
*/

#include "DirReader.hpp"

DirReader::DirReader()
: _dir(nullptr)
{
}

DirReader::DirReader(const std::string &path) noexcept(false)
: _dir(nullptr)
{
    load(path);
}

DirReader::~DirReader()
{
    closedir(_dir);
}

void DirReader::load(const std::string &path) noexcept(false)
{
    _path = path;
    refresh();
}

void DirReader::refresh() noexcept(false)
{
    if (_dir != nullptr)
        closedir(_dir);
    _files.clear();

    _dir = opendir(_path.c_str());
    if (_dir == nullptr)
        throw std::invalid_argument(_path + strerror(errno));
    while (true) {
        _files.push_back(readdir(_dir));
        if (_files.back() == nullptr) {
            _files.pop_back();
            break;
        }
    }
}

const std::string &DirReader::getName() const { return _path; }

const std::vector<std::string> &DirReader::getAllFiles() const
{
    static std::vector<std::string> vect;
    auto f = _files.begin();

    vect.clear();
    vect.resize(_files.size());

    for (size_t i = 0; i < _files.size() && f != _files.end(); i++, f++)
        vect[i] = (*f)->d_name;
    return vect;
}

const std::vector<std::string> &DirReader::getFiles() const
{
    static std::vector<std::string> vect;
    auto f = _files.begin();

    vect.clear();
    vect.resize(std::count_if(_files.begin(), _files.end(), [](struct dirent *d) { return d->d_type == DT_REG; }));

    for (size_t i = 0; f != _files.end(); ++f)
        if ((*f)->d_type == DT_REG) {
            vect[i] = (*f)->d_name;
            ++i;
        }
    return vect;
}

const std::vector<std::string> &DirReader::getFiles(const std::string &regex) const
{
    static std::vector<std::string> vect;
    auto f = _files.begin();
    const std::regex re(regex);

    vect.clear();
    vect.resize(std::count_if(_files.begin(), _files.end(), [&re](struct dirent *d) { return std::regex_search(d->d_name, re); }));

    for (size_t i = 0; f != _files.end(); ++f)
        if (std::regex_search((*f)->d_name, re)) {
            vect[i] = (*f)->d_name;
            ++i;
        }
    return vect;
}

const std::vector<std::string> &DirReader::getDirectory() const
{
    static std::vector<std::string> vect;
    auto f = _files.begin();

    vect.clear();
    vect.resize(std::count_if(_files.begin(), _files.end(), [](struct dirent *d) { return d->d_type == DT_DIR; }));

    for (size_t i = 0; f != _files.end(); ++f)
        if ((*f)->d_type == DT_DIR) {
            vect[i] = (*f)->d_name;
            ++i;
        }
    return vect;
}