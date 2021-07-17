/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** PointerHandler
*/

#pragma once

#include <map>
#include <string>
#include <memory>
#include <functional>

class Material;

class PointerHandler {
    public:
        ~PointerHandler() = default;

        static std::map<std::string, std::unique_ptr<Material>> materials;

    protected:
    private:
};