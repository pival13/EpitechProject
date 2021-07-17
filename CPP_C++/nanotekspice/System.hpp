/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** System
*/

#pragma once

#include "ISystem.hpp"
#include "my_except.hpp"

#include "Component/Component.hpp"

#include <csignal>
#include <regex>
#include <fstream>

namespace nts {
    class System : public ISystem {
        public:
            System(const std::string &file);
            ~System();

            void display() const;
            void simulate();
            void dump() const;
            void loop();
            void assign(const std::string &name, const std::string &state, bool init_assign);
            std::unique_ptr<IComponent> createComponent(const std::string &type, const std::string &value);

        private:
            void read_file(const std::string &file);
            void read_chipsets(const std::string &str);
            void read_links(const std::string &str);

            std::map<std::string, std::unique_ptr<IComponent>> _components;
    };
}