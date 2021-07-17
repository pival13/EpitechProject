/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** DLLoader
*/

#pragma once

#include <dlfcn.h>
#include <iostream>

class DLLoader {
    public:
        DLLoader();
        DLLoader(const std::string &path) noexcept(false);
        ~DLLoader();

        void load(const std::string &path) noexcept(false);

        template <typename T>
        T *getFunction(const std::string &fName) const noexcept(false) { 
            if (lib == nullptr)
                throw std::invalid_argument("Uninitialized DLLoader");
            T *f = (T *)dlsym(lib, fName.c_str());
            if (f == nullptr)
                throw std::invalid_argument(dlerror());
            return f;
        }

    private:
        void *lib;
};
