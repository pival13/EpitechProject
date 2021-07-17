/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** ParserArcadeFileTexture
*/

#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>

class ParserArcadeFileTexture {
    public:
        ParserArcadeFileTexture(const std::string &filepath);
        ~ParserArcadeFileTexture();

        const std::vector<char> getSymbols() const;
        const std::string getFilePath(char symb) const;
        const std::array<size_t, 5> getTextureRect(char symb) const;
        const std::array<char, 2> getChar(char symb) const;
        const std::array<size_t, 2> getColor(char symb) const;

    private:
        const std::string _filepath;
        std::map<char,const std::string> _files;
};
