/*
** EPITECH PROJECT, 2020
** CPPOabel
** File description:
** GetOpt
*/

#include "GetOpt.hpp"

std::list<argOption> GetOpt(const std::list<char *> &args, const std::list<argOption> &opts)
{
    std::list<argOption> options;

    for (const argOption &opt : opts) {
        for (auto it = args.begin(); it != args.end(); ++it) {
            std::cmatch match;
            if (opt.hasArg != MandatoryArg && "--" + opt.longOpt == *it)
                options.emplace_back(opt.shortOpt, opt.longOpt, opt.hasArg, *it);
            else if (opt.hasArg != NoArg && std::regex_match(*it, match, std::regex("--" + opt.longOpt + "=(.+)")))
                options.emplace_back(opt.shortOpt, opt.longOpt, opt.hasArg, match[1].str());
            else if (opt.hasArg != NoArg && *it == "--" + opt.longOpt) {
                auto it2 = it;
                if (++it2 != args.end())
                    options.emplace_back(opt.shortOpt, opt.longOpt, opt.hasArg, *it2);
            } else if (opt.hasArg != NoArg && *it == std::string("-") + opt.shortOpt) {
                auto it2 = it;
                if (++it2 != args.end())
                    options.emplace_back(opt.shortOpt, opt.longOpt, opt.hasArg, *it2);
            } else if (opt.hasArg != MandatoryArg && std::regex_match(*it, std::regex("-(?!-.*)(.*"+std::string(1, opt.shortOpt)+".*)")))
                options.emplace_back(opt.shortOpt, opt.longOpt, opt.hasArg, *it);
            else if (opt.hasArg != NoArg && std::regex_match(*it, match, std::regex("-" + std::string(1, opt.shortOpt) + "(.+)")))
                options.emplace_back(opt.shortOpt, opt.longOpt, opt.hasArg, match[1].str());
        }
    }
    return options;
}
