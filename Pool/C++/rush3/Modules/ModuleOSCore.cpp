/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** ModuleOSCore
*/

#include "ModuleOSCore.hpp"

ModuleOSCore::ModuleOSCore()
: AModuleOneTime("Informations system")
{
    update();
}

ModuleOSCore::~ModuleOSCore()
{
}

void ModuleOSCore::update()
{
    std::ifstream f("/proc/sys/kernel/osrelease");
    if (!f.is_open())
        _info["Kernel"] = "[no information on kernel version]";
    else
        std::getline(f, _info["Kernel"]);
    f.close();

    f.open("/etc/os-release");
    _info["OSName"] = "[no information on OS name]";
    if (f.is_open())
        while (!f.eof()) {
            std::string s;
            std::smatch rmatch;

            std::getline(f, s);
            if (std::regex_match(s, rmatch, std::regex("NAME=\"(.*)\""))) {
                _info["OSName"] = rmatch[1].str();
                break;
            } else if (std::regex_match(s, rmatch, std::regex("PRETTY_NAME=\"(.*)\"")))
                _info["OSName"] = rmatch[1].str();
        }
    f.close();
}