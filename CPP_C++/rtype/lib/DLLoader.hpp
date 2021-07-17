/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** DLLoader
*/

#pragma once

#include <filesystem>

#ifndef DllExport
    #ifdef _WIN32
        #define DllExport extern "C" __declspec(dllexport)
    #else
        #define DllExport extern "C" __attribute__((__visibility__("default")))
    #endif
#endif
#ifdef DLL_NAME
    #undef DLL_NAME
#endif
#ifdef DLL_CREATE
    #undef DLL_CREATE
#endif
#ifdef DLL_FREE
    #undef DLL_FREE
#endif
#if defined _WIN32
    #include <windows.h>
    #define DLL_NAME(_path, libName) std::filesystem::path(_path + "/" + libName + ".dll").string()
    #define DLL_CREATE(libName) LoadLibrary(TEXT( libName ))
    #define DLL_FREE FreeLibrary
#elif defined __APPLE__
    #include <dlfcn.h>
    #define DLL_NAME(_path, libName) std::filesystem::path(_path + "/lib" + libName + ".dylib").string()
    #define DLL_CREATE(libName) dlopen( libName, RTLD_LAZY )
    #define DLL_FREE dlclose
#elif defined __unix__
    #include <dlfcn.h>
    #define DLL_NAME(_path, libName) std::filesystem::path(_path + "/lib" + libName + ".so").string()
    #define DLL_CREATE(libName) dlopen( libName, RTLD_LAZY )
    #define DLL_FREE dlclose
#else
    #error DLLoader compiled with an unknow operating system
#endif

#include <iostream>

class DLLoader {
    public:
        DLLoader();
        DLLoader(const DLLoader &other);
        DLLoader(const std::string &path, const std::string &libraryName);
        DLLoader(const std::string &libraryName);
        ~DLLoader();

        void load(const std::string &path, const std::string &libraryName);

        DLLoader &operator=(const DLLoader &other);
        operator bool() const;

        template <typename T>
        T *getFunction(const std::string &fName) const { 
            if (lib == nullptr)
                throw std::invalid_argument("Uninitialized DLLoader");
            
            #ifdef _WIN32
            T *f = (T *)GetProcAddress(lib, fName.c_str());
            #else
            T *f = (T *)dlsym(lib, fName.c_str());
            #endif

            if (f == nullptr)
                #ifdef _WIN32
                throw std::invalid_argument("Failed to retrieved function \""+fName+"\"");
                #else
                throw std::invalid_argument(dlerror());
                #endif
            return f;
        }

    private:
        void _load(const std::string &lib);

    private:
    #ifdef _WIN32
        HMODULE lib;
    #else
        void *lib;
    #endif
        std::string libName;
};
