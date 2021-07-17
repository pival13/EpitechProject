/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** DirReader
*/

#pragma once

#include <filesystem>

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <regex>

class DirReader {
    public:
        DirReader();
        DirReader(const std::string &path);
        ~DirReader();

        void load(const std::string &path);
        void refresh();
        std::vector<std::string> getAll(const std::string &regex=".*") const;
        std::vector<std::string> getFiles(const std::string &regex=".*") const;
        std::vector<std::string> getDirectories(const std::string &regex=".*") const;
        std::string getPath() const;

    private:
        std::filesystem::path _path;
        std::list<std::filesystem::directory_entry> _files;
};
