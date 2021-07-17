/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** DirReader
*/

#pragma once

#include <dirent.h>
#include <string.h>
#include <errno.h>

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <regex>

class DirReader {
    public:
        DirReader();
        DirReader(const std::string &path) noexcept(false);
        ~DirReader();

        void load(const std::string &path) noexcept(false);
        void refresh() noexcept(false);
        const std::vector<std::string> &getAllFiles() const;
        const std::vector<std::string> &getFiles() const;
        const std::vector<std::string> &getFiles(const std::string &regex) const;
        const std::vector<std::string> &getDirectory() const;
        const std::string &getName() const;

    private:
        std::string _path;
        DIR *_dir;
        std::list<struct dirent *> _files;
};
