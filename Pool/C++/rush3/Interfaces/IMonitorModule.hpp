/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** IMonitorModule
*/

#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <list>
#include <vector>
#include <array>

using oneTimeInfo = std::map<std::string, std::string>;
using sixtyTimeInfo = std::map<std::string, std::list<std::string>>;

class IMonitorModule {
    public:
        virtual ~IMonitorModule() {}

        virtual const std::string &getName() const = 0;
        virtual bool getStatus() const = 0;
        virtual bool isDrawable() const = 0;
        virtual void setStatus(bool status) = 0;
        virtual oneTimeInfo getOneInfo() const = 0;
        virtual sixtyTimeInfo getSixtyInfo() const = 0;

        virtual void update() = 0;
};
