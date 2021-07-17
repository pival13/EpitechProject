/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** ParserArcadeFileTexture
*/

#include "ParserArcadeFileTexture.hpp"
#include <iostream>
ParserArcadeFileTexture::ParserArcadeFileTexture(const std::string &filepath)
: _filepath(filepath)
{
    std::ifstream f(filepath);

    if (!f.is_open())
        throw std::runtime_error("Can't open file " + filepath);
    while (f.is_open() && !f.eof()) {
        std::string line;
        std::getline(f, line);
        std::smatch sm;
        if (std::regex_search(line, sm, std::regex("(.) (.* \\d+ \\d+ \\d+ \\d+ \\d+ .. \\d+ \\d+)")))
            _files.insert(std::pair<char,const std::string>(sm[1].str()[0], sm[2].str()));
    }
    if (f.is_open())
        f.close();
}

ParserArcadeFileTexture::~ParserArcadeFileTexture()
{
}

const std::vector<char> ParserArcadeFileTexture::getSymbols() const
{
    std::vector<char> vect;

    for (std::pair<char, std::string> pair : _files)
        vect.insert(vect.end(), pair.first);
    return vect;
}

const std::string ParserArcadeFileTexture::getFilePath(char symb) const
{
    std::smatch sm;
    if (std::regex_match(_files.at(symb), sm, std::regex("(.*) \\d+ \\d+ \\d+ \\d+ \\d+ .. \\d+ \\d+")))
        return _filepath.substr(0, _filepath.find_last_of("/") + 1) + sm[1].str();
    return "";
}

const std::array<size_t, 5> ParserArcadeFileTexture::getTextureRect(char symb) const
{
    std::smatch sm;
    if (std::regex_match(_files.at(symb), sm, std::regex(".* (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) .. \\d+ \\d+")))
        return {std::stoul(sm[1].str()),std::stoul(sm[2].str()),std::stoul(sm[3].str()),std::stoul(sm[4].str()),std::stoul(sm[5].str())};
    return {0,0,0,0,0};
}

const std::array<char, 2> ParserArcadeFileTexture::getChar(char symb) const
{
    std::smatch sm;
    if (std::regex_match(_files.at(symb), sm, std::regex(".* \\d+ \\d+ \\d+ \\d+ (.)(.) \\d+ \\d+")))
        return {sm[1].str()[0],sm[2].str()[0]};
    return {'\0','\0'};
}

const std::array<size_t, 2> ParserArcadeFileTexture::getColor(char symb) const
{
    std::smatch sm;
    if (std::regex_match(_files.at(symb), sm, std::regex(".* \\d+ \\d+ \\d+ \\d+ .. (\\d+) (\\d+)")))
        return {std::stoul(sm[1].str()),std::stoul(sm[2].str())};
    return {0,0};
}