/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** TextualDisplay
*/

#include "TextualDisplay.hpp"

TextualDisplay::TextualDisplay()
: _array(), _isEnd(false), _shouldDraw(false)
{
    for (size_t i = 0; i != _array.size(); i++)
        for (size_t j = 0; j != _array[i].size(); j++)
            drawStr(i, j, " ");
    initWindow();
    _modules.push_back(new ModuleName());
    _modules.push_back(new ModuleOSCore());
    _modules.push_back(new ModuleDatetime());
    _modules.push_back(new ModuleMemory());
    _modules.push_back(new ModuleCPU());
    _modules.push_back(new ModuleNetwork());
    _drawFunc.push_back(&TextualDisplay::drawBorder);
    _drawFunc.push_back(&TextualDisplay::drawLowBar);
    _drawFunc.push_back(&TextualDisplay::drawModuleName);
    _drawFunc.push_back(&TextualDisplay::drawOSCore);
    _drawFunc.push_back(&TextualDisplay::drawDatetime);
    _drawFunc.push_back(&TextualDisplay::drawRAM);
    _drawFunc.push_back(&TextualDisplay::drawCPU);
    _drawFunc.push_back(&TextualDisplay::drawNetwork);
}

TextualDisplay::~TextualDisplay()
{
    endwin();
    for (IMonitorModule *module : _modules)
        delete module;
}

void TextualDisplay::initWindow()
{
    if (!(initscr())) {
        std::cerr << ("Cannot init term.\n") << std::endl;
        exit(1);
    }
    start_color();
    init_pair(1, 1, 0);
    init_pair(2, 2, 0);
    init_pair(3, 3, 0);
    init_pair(4, 4, 0);
    init_pair(5, 5, 0);
    init_pair(6, 6, 0);
    init_pair(7, 7, 0);
    curs_set(false);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    noecho();
}

void TextualDisplay::updateModules()
{
    for (IMonitorModule *module : _modules)
        module->update();
    _shouldDraw = true;
}

void TextualDisplay::drawStr(int y, int x, const char *str, int color)
{
    if (color != 0)
        attron(COLOR_PAIR(color));
    mvprintw((LINES-30)/2+y, (COLS-120)/2+x, str);
    if (color != 0)
        attroff(COLOR_PAIR(color));
}

void TextualDisplay::drawModuleName()
{
    if (_modules[0]->getStatus())
    {
        oneTimeInfo info = _modules[0]->getOneInfo();
        std::string usr = "Username: ";
        std::string host = "Hostname: ";
        drawStr(1, 2, usr.c_str(), 6);
        drawStr(1, usr.size() + 2, info["Username"].c_str());
        drawStr(1, 30, host.c_str(), 6);
        drawStr(1, 30 + host.size(), info["Hostname"].c_str());
    }
}

void TextualDisplay::drawOSCore()
{
    if (_modules[1]->getStatus())
    {
        oneTimeInfo info = _modules[1]->getOneInfo();
        std::string kern = "Kernel: ";
        std::string os = "OS Name: ";
        drawStr(3, 2, os.c_str(), 6);
        drawStr(3, os.size() + 2, info["OSName"].c_str());
        drawStr(3, 30, kern.c_str(), 6);
        drawStr(3, 30 + kern.size(), info["Kernel"].c_str());
    }
}

void TextualDisplay::drawDatetime()
{
    if (_modules[2]->getStatus())
    {
        oneTimeInfo info = _modules[2]->getOneInfo();
        std::string date = "Date: ";
        std::string time = "Time: ";
        drawStr(5, 2, date.c_str(), 6);
        drawStr(5, date.size() + 2, info["Date"].c_str());
        drawStr(5, 30, time.c_str(), 6);
        drawStr(5, 30 + time.size(), info["Time"].c_str());
    }
}

void TextualDisplay::drawInlineGraph(int x, int y, int percent, const std::string &name, int prcYell, int prcRed)
{
    drawStr(y, x, name.c_str(), 6);

    drawStr(y, x+9, "[");
    for (int i = 0; i < percent * 0.4f; i++)
        drawStr(y, x + 10 + i, "|", 2);
    for (int i = 0; i < prcYell * 0.4f; i++)
        drawStr(y, x + 10 + percent * 0.4f + i, "|", 3);
    for (int i = 0; i < prcRed * 0.4f; i++)
        drawStr(y, x + 10 + percent * 0.4f + prcYell * 0.4f + i, "|", 1);
    drawStr(y, x + 50, "]");

    std::string strPercent = std::to_string(percent + prcYell + prcRed) + "%%";
    drawStr(y, x + 57 - strPercent.length(), strPercent.c_str());
}

void TextualDisplay::drawRAM()
{
    if (_modules[3]->getStatus())
    {
        sixtyTimeInfo info = _modules[3]->getSixtyInfo();
        int memPercent = (stoi(info["MemTotal"].front()) - stoi(info["MemFree"].front()) - stoi(info["Buffers"].front()) - stoi(info["Cached"].front())) * 100 / stoi(info["MemTotal"].front());
        int swapPercent = (stoi(info["SwapTotal"].front()) - stoi(info["SwapFree"].front())) * 100 / stoi(info["SwapTotal"].front());
        drawInlineGraph(62, 2, memPercent, "Memory:", (stoi(info["Buffers"].front()) * 100 / stoi(info["MemTotal"].front())), (stoi(info["Cached"].front()) * 100 / stoi(info["MemTotal"].front())));
        drawInlineGraph(62, 4, swapPercent, "Swap:");
    }
}

void TextualDisplay::drawCPU()
{
    if (_modules[4]->getStatus())
    {
        sixtyTimeInfo info = _modules[4]->getSixtyInfo();
        std::string CPUmod = "CPU Model:";
        std::string CPUcores = "Cores:";
        std::string CPUmax = "Max frequency:";
        drawStr(9, 2, CPUmod.c_str(), 6);
        drawStr(9, 3 + CPUmod.size(), info["model name"].front().c_str());
        drawStr(9, 12 + CPUmod.size() + info["model name"].front().size(), CPUcores.c_str(), 6);
        drawStr(9, 13+ CPUmod.size() + info["model name"].front().size() + CPUcores.size(), info["cpu cores"].front().c_str());
        drawStr(9, 39 + CPUmod.size() + info["model name"].front().size() + CPUcores.size() + info["cpu cores"].front().size(), CPUmax.c_str(), 6);
        drawStr(9, 40 + CPUmod.size() + info["model name"].front().size() + CPUcores.size() + info["cpu cores"].front().size() + CPUmax.size(), (std::to_string(stoi(info["MaxFreq"].front()) / 1000) + "MHz").c_str());
        for (size_t cpuNb = 0; cpuNb < info.size() - 3; cpuNb++)
        {
            int cpuPercent = stof(info["CPU " + std::to_string(cpuNb)].front()) * 100000 / stoi(info["MaxFreq"].front());
            drawInlineGraph((cpuNb % 2) * 60 + 2, 11 + cpuNb / 2 * 2, cpuPercent, "CPU " + std::to_string(cpuNb) + ":");
        }
    }
}

void TextualDisplay::drawNetwork()
{
    if (_modules[5]->getStatus())
    {
        sixtyTimeInfo info = _modules[5]->getSixtyInfo();
        std::string netInt = "Active network interface:";
        std::string netByteR = "Data received:";
        std::string netByteT = "Data transmitted:";
        drawStr(22, 60 - netInt.size() / 2 - info["Type"].front().size() / 2, netInt.c_str(), 6);
        drawStr(22, 62 + netInt.size() / 2 - info["Type"].front().size() / 2, info["Type"].front().c_str());
        drawStr(24, 30 - netByteR.size() / 2, netByteR.c_str(), 6);
        drawStr(25, 30 - info["Input"].front().size() / 2, (std::to_string(stoi(info["Input"].front()) / 1000) + " kB").c_str());
        drawStr(24, 90 - netByteT.size() / 2, netByteT.c_str(), 6);
        drawStr(25, 90 - info["Output"].front().size() / 2, (std::to_string(stoi(info["Output"].front()) / 1000) + " kB").c_str());
    }
}

void TextualDisplay::drawLowBar()
{
    std::string activeUser = "[x] User/Host - <u> |";
    std::string activeOS = "[x] OS/Kernel - <o> |";
    std::string activeDate = "[x] Date/Time - <d> |";
    std::string activeRAM = "[x] RAM - <r> |";
    std::string activeCPU = "[x] CPU - <c> |";
    std::string activeNetwork = "[x] Network - <n>";

    size_t offset = 2;
    drawStr(29, offset, activeUser.c_str());
    drawStr(29, offset + 1, _modules[0]->getStatus() ? "x" : " ", 6);
    offset += activeUser.length() + 1;

    drawStr(29, offset, activeOS.c_str());
    drawStr(29, offset + 1, _modules[1]->getStatus() ? "x" : " ", 6);
    offset += activeOS.length() + 1;

    drawStr(29, offset, activeDate.c_str());
    drawStr(29, offset + 1, _modules[2]->getStatus() ? "x" : " ", 6);
    offset += activeDate.length() + 1;

    drawStr(29, + offset, activeRAM.c_str());
    drawStr(29, offset + 1, _modules[3]->getStatus() ? "x" : " ", 6);
    offset += activeRAM.length() + 1;

    drawStr(29, offset, activeCPU.c_str());
    drawStr(29, offset + 1, _modules[4]->getStatus() ? "x" : " ", 6);
    offset += activeCPU.length() + 1;

    drawStr(29, offset, activeNetwork.c_str());
    drawStr(29, offset + 1, _modules[5]->getStatus() ? "x" : " ", 6);
    offset += activeNetwork.length() + 1;
}

void TextualDisplay::drawBorder()
{
    if (LINES > (int)_array.size()) {
        mvhline((LINES-_array.size())/2-1, (COLS-_array[0].size())/2, ACS_HLINE,_array[0].size());
        mvhline((LINES-_array.size())/2 + _array.size(), (COLS-_array[0].size())/2, ACS_HLINE,_array[0].size());
    }
    if (COLS > (int)_array[0].size()) {
        mvvline((LINES-_array.size())/2, (COLS-_array[0].size())/2-1, ACS_VLINE, _array.size());
        mvvline((LINES-_array.size())/2, (COLS-_array[0].size())/2 + _array[0].size(), ACS_VLINE, _array.size());
    }
    mvaddch((LINES-_array.size())/2-1, (COLS-_array[0].size())/2-1, ACS_ULCORNER);
    mvaddch((LINES-_array.size())/2-1, (COLS-_array[0].size())/2 + _array[0].size(), ACS_URCORNER);
    mvaddch((LINES-_array.size())/2 + _array.size(), (COLS-_array[0].size())/2-1, ACS_LLCORNER);
    mvaddch((LINES-_array.size())/2 + _array.size(), (COLS-_array[0].size())/2 + _array[0].size(), ACS_LRCORNER);

    for (size_t i = 0; i != _array[0].size(); i++) {
        drawStr(7, i, "_");
        drawStr(19, i, "_");
        drawStr(28, i, "_");
    }
    for (size_t i = 0; i != 7; i++)
        drawStr(i, _array[i].size()/2-1, "|");
}

void TextualDisplay::drawModules()
{
    if (!_shouldDraw)
        return;

    clear();
    if (LINES >= 30 && COLS >= 120) {
        for (size_t i = 0; i != _drawFunc.size(); i++)
            (this->*_drawFunc[i])();
    } else {
        mvprintw(LINES/2, COLS/2-14, "Please enlarge the windows");
        mvprintw(LINES/2+1, COLS/2-11, "Minimum size: 30x120");
    }
    refresh();
    _shouldDraw = false;
}

void TextualDisplay::getEvents()
{
    int c = getch();

    if (c == ERR)
        return;
    if (c == 'u')
        _modules[0]->setStatus(!_modules[0]->getStatus());
    if (c == 'o')
        _modules[1]->setStatus(!_modules[1]->getStatus());
    if (c == 'd')
        _modules[2]->setStatus(!_modules[2]->getStatus());
    if (c == 'r')
        _modules[3]->setStatus(!_modules[3]->getStatus());
    if (c == 'c')
        _modules[4]->setStatus(!_modules[4]->getStatus());
    if (c == 'n')
        _modules[5]->setStatus(!_modules[5]->getStatus());
    if (c == 'q' || c == 'Q')
        _isEnd = true;
    _shouldDraw = true;
}

bool TextualDisplay::isEnd() const { return _isEnd; }
