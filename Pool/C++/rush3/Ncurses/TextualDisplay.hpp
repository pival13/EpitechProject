/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** TextualDisplay
*/

#pragma once

#include <ncurses.h>
#include "../Interfaces/IMonitorDisplay.hpp"
#include "../Modules/ModuleName.hpp"
#include "../Modules/ModuleOSCore.hpp"
#include "../Modules/ModuleDatetime.hpp"
#include "../Modules/ModuleMemory.hpp"
#include "../Modules/ModuleCPU.hpp"
#include "../Modules/ModuleNetwork.hpp"

class TextualDisplay : public IMonitorDisplay
{
    public:
        TextualDisplay();
        ~TextualDisplay();

        void updateModules();
        void drawModules();
        void getEvents();
        bool isEnd() const;

    private:
        void initWindow();
        void drawModuleName();
        void drawOSCore();
        void drawDatetime();
        void drawRAM();
        void drawCPU();
        void drawNetwork();
        void drawBorder();
        void drawLowBar();
        void drawStr(int y, int x, const char *str, int color = 0);
        void drawInlineGraph(int x, int y, int percent, const std::string &name, int prcBlue = 0, int prcRed = 0);

        std::array<std::array<char, 120>, 30> _array;
        std::vector<IMonitorModule *> _modules;
        std::vector<void (TextualDisplay::*)()> _drawFunc;
        bool _isEnd;
        bool _shouldDraw;
};
