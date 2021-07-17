/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** AModuleSixtyTime
*/

#pragma once

#include "../Interfaces/IMonitorModule.hpp"

class AModuleSixtyTime : public IMonitorModule {
    public:
        AModuleSixtyTime(const std::string &name, const std::string &filepath);
        ~AModuleSixtyTime();

        const std::string &getName() const;
        bool getStatus() const;
        bool isDrawable() const;
        oneTimeInfo getOneInfo() const;
        sixtyTimeInfo getSixtyInfo() const;
        void setStatus(bool status);

    protected:
        void updateMap(std::ifstream&, std::map<std::string, std::list<std::string>>&, const std::vector<std::regex>&);

    private :
        const std::string _name;
        bool _isActive;

    protected:
        const std::string _filepath;
        sixtyTimeInfo _info;
};
