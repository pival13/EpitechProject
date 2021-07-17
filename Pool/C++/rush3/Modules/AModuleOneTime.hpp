/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** AModuleOneTime
*/

#pragma once

#include "../Interfaces/IMonitorModule.hpp"

class AModuleOneTime : public IMonitorModule {
    public:
        AModuleOneTime(const std::string &name);
        ~AModuleOneTime();

        const std::string &getName() const;
        bool getStatus() const;
        bool isDrawable() const;
        oneTimeInfo getOneInfo() const;
        sixtyTimeInfo getSixtyInfo() const;
        void setStatus(bool status);

    private:
        const std::string _name;
        bool _isActive;

    protected:
        oneTimeInfo _info;
};
