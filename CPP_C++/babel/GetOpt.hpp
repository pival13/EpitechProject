/*
** EPITECH PROJECT, 2020
** CPP_babel
** File description:
** GetOpt
*/

#pragma once

#include <map>
#include <list>
#include <regex>
#include <string>
#include <iostream>
#include <algorithm>

enum optionHasArg {
    NoArg,
    MandatoryArg
};

struct argOption {
    argOption(char so, const std::string &lo, optionHasArg ar, const std::string &v="")
        : shortOpt(so), longOpt(lo), hasArg(ar), value(v) {}

    char shortOpt;
    std::string longOpt;
    optionHasArg hasArg;
    std::string value;
};

std::list<argOption> GetOpt(const std::list<char *> &args, const std::list<argOption> &opts);