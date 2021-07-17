
/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** System
*/

#include "System.hpp"

nts::System::System(const std::string &file)
{
    read_file(file);
    if (_components.size() < 2)
        throw my_except("Incomplete file");

    // std::pair<const std::string, std::unique_ptr<IComponent>>
    // std::pair<name, unique_ptr<comp>>
    for (auto &comp : _components)
        if (!comp.second.get()->isLinked())
            throw my_except(comp.second.get()->getType() + " \"" + comp.second.get()->getName() +
                 "\" is not linked to any other component");
}

nts::System::~System()
{
}

void nts::System::display() const
{
    // std::pair<name, unique_ptr<comp>>
    for (auto &comp : _components) {
        ComponentOutput *output = dynamic_cast<ComponentOutput *>(comp.second.get());
        if (output)
            std::cout << *output << std::endl;
    }
}

void nts::System::simulate()
{
    // std::pair<name, unique_ptr<comp>>
    for (auto &comp : _components)
        comp.second.get()->reset();
    for (auto &comp : _components)
        if (dynamic_cast<ComponentOutput *>(comp.second.get()))
            comp.second.get()->compute();
}

void nts::System::dump() const
{
    // std::pair<name, unique_ptr<comp>>
    for (auto &comp : _components)
        comp.second.get()->dump();
}

static bool &looping()
{
    static bool looping = false;
    return looping;
}

static void sigintCallback(int)
{
    looping() = false;
}

void nts::System::loop()
{
    looping() = true;

    signal(SIGINT, sigintCallback);
    while (looping())
        simulate();
}

void nts::System::assign(const std::string &name, const std::string &state, bool init_assign)
{
    nts::ComponentInput *comp = dynamic_cast<ComponentInput *>(_components.at(name).get());
    
    if (!comp || (!init_assign && dynamic_cast<ComponentClock *>(_components.at(name).get())))
        throw my_except("Assignement to a non-input component: \"" + name + "\"");
    if (state == "1")
        comp->setState(nts::TRUE);
    else if (state == "0")
        comp->setState(nts::FALSE);
    else
        throw my_except("Assignement with unknow value");
}

std::unique_ptr<nts::IComponent> nts::System::createComponent(const std::string &type, const std::string &str)
{
    if (type == "input")
        return std::unique_ptr<IComponent>(new ComponentInput(str));
    else if (type == "output")
        return std::unique_ptr<IComponent>(new ComponentOutput(str));
    else if (type == "clock")
        return std::unique_ptr<IComponent>(new ComponentClock(str));
    else if (type == "true")
        return std::unique_ptr<IComponent>(new ComponentTrue(str));
    else if (type == "false")
        return std::unique_ptr<IComponent>(new ComponentFalse(str));
    else if (type == "4001")
        return std::unique_ptr<IComponent>(new Component4001(str));
    else if (type == "4008")
        return std::unique_ptr<IComponent>(new Component4008(str));
    else if (type == "4011")
        return std::unique_ptr<IComponent>(new Component4011(str));
    else if (type == "4013")
        return std::unique_ptr<IComponent>(new Component4013(str));
    else if (type == "4017")
        return std::unique_ptr<IComponent>(new Component4017(str));
    else if (type == "4030")
        return std::unique_ptr<IComponent>(new Component4030(str));
    else if (type == "4040")
        return std::unique_ptr<IComponent>(new Component4040(str));
    else if (type == "4069")
        return std::unique_ptr<IComponent>(new Component4069(str));
    else if (type == "4071")
        return std::unique_ptr<IComponent>(new Component4071(str));
    else if (type == "4081")
        return std::unique_ptr<IComponent>(new Component4081(str));
    else if (type == "4094")
        return std::unique_ptr<IComponent>(new Component4094(str));
    else if (type == "4514")
        return std::unique_ptr<IComponent>(new Component4514(str));
    else
        throw my_except("Creation of unknow component: " + type + ", entitled: " + str);
}

void nts::System::read_file(const std::string &file)
{   
    std::ifstream f(file);
    std::string str;
    int state = 0;

    if (!f.is_open())
        throw my_except("Can't open file");
    std::getline(f, str);

    while (!f.eof() || str.length() > 0) {
        if (std::regex_match(str, std::regex(".chipsets:\\s*(#.*)?")) && state == 0)
            state = 1;
        else if (std::regex_match(str, std::regex(".links:\\s*(#.*)?")) && state == 1)
            state = 2;
        else if (state == 1)
            read_chipsets(str);
        else if (state == 2)
            read_links(str);
        else if (!std::regex_match(str, std::regex("\\s*(#.*)?")))
            throw my_except("Bad line: " + str);

        if (f.eof())
            break;
        std::getline(f, str);
    }
    if (state != 2)
        throw my_except("Incomplete input file");
}

void nts::System::read_chipsets(const std::string &str)
{
    std::smatch match;

    if (std::regex_match(str, std::regex("\\s*(#.*)?")))
        return;
    else if (std::regex_match(str, match, std::regex("\\s*([^\\s]+)\\s+([^\\s#]+)\\s*(#.*)?"))) {
        if (_components.count(match[2].str()))
            throw my_except("Redefinition of component \"" + match[2].str() + "\"");
        _components.insert(std::pair<std::string, std::unique_ptr<IComponent>>(match[2].str(), createComponent(match[1].str(), match[2].str())));
    } else
        throw my_except("Bad component declaration: " + str);
}

void nts::System::read_links(const std::string &str)
{
    std::smatch match;

    if (std::regex_match(str, std::regex("\\s*(#.*)?")))
        return;
    else if (std::regex_match(str, match,std::regex("\\s*([^:]+):(\\d+)\\s+([^:]+):(\\d+)\\s*(#.*)?"))) {
        for (size_t i : {1, 3})
            if (!_components.count(match[i].str()))
                throw my_except("Invalid component while linking: " + match[i].str());  
        _components.at(match[1].str()).get()->setLink(stoi(match[2].str()), *_components.at(match[3].str()).get(), stoi(match[4].str()));
    } else
        throw my_except("Bad linking: " + str);
}