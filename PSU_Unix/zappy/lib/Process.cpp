/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Process
*/

#include "Process.hpp"
#include <cstdlib>
#include <cstring>
#include <algorithm>

std::list<Process> Process::_processes;

Process::Process(const std::string &cmdLine)
{
    size_t nb = std::count(cmdLine.begin(), cmdLine.end(), ' ') + 1;
    char **tbl = (char **)alloca(sizeof(char*) * (nb+1));
    tbl[nb] = nullptr;

    for (size_t pos = 0, i = 0; i < nb; i++) {
        std::string s2 = cmdLine.substr(pos, cmdLine.find(' ', pos)-pos);
        tbl[i] = (char *)alloca(sizeof(char *) * (s2.length()+1));
        strcpy(tbl[i], s2.c_str());
        pos = cmdLine.find(' ', pos);
        if (pos != std::string::npos)
            pos++;
    }

    launchProcess([&tbl]() {
        return execvp(tbl[0], tbl);
    });
}

Process::Process(std::function<int()> main)
{
    launchProcess(main);
}
/*
Process::Process(std::function<int(Process &)> main)
{
    launchProcessIPC(main);
}
*/
Process::Process(std::function<int(int,char*[])> main, int argc, char *argv[])
{
    launchProcess([&main, &argc, &argv]() { return main(argc, argv); });
}

Process::Process(std::function<int(int,char*[],char*[])> main, int argc, char *argv[], char *env[])
{
    launchProcess([&main, &argc, &argv, &env]() { return main(argc, argv, env); });
}

Process::Process(Process &&p) { *this = std::move(p); }

Process &Process::operator=(Process &&rhs)
{
   // _ipc.reset();
    for (Process &p : _processes)
        p.detach();
    _processes.clear();

    pid = rhs.pid;
    _joinable = rhs._joinable;
   // _ipc = std::move(rhs._ipc);
    _processes = std::move(rhs._processes);

    rhs.pid = 0;
    rhs._joinable = false;
    return *this;
}

Process::~Process()
{
    if (_joinable)
        abort();
}

void Process::launchProcess(std::function<int()> main)
{
    pid = fork();
    if (pid == -1) {
        _joinable = false;
    } else if (pid == 0) {
        for (Process &p : _processes)
            p._joinable = false;
        _processes.clear();
        std::exit(main());
    } else
        _joinable = true;
}
/*
void Process::launchProcessIPC(std::function<int(Process &)> main)
{
    _ipc = std::make_unique<PipeIPC>();
    parentPid = getpid();
    pid = fork();
    if (pid == -1) {
        _joinable = false;
    } else if (pid == 0) {
        for (Process &p : _processes)
            p._joinable = false;
        _processes.clear();
        _ipc->prepareOtherSide();
        std::exit(main(*this));
    } else {
        _ipc->prepareFirstSide();
        _joinable = true;
    }
}
*/
int Process::join()
{
    if (!_joinable)
        throw std::system_error(EINVAL, std::generic_category());
    int ret = 0;

    waitpid(pid, &ret, 0);
    _joinable = false;
    return WEXITSTATUS(ret);
}

void Process::detach()
{
    if (!_joinable)
        throw std::system_error(EINVAL, std::generic_category());
    kill(getpid(), SIGCHLD);
    _joinable = false;
}
/*
IPData Process::receiveData()
{
    while (isAlive()) {
        IPData data = _ipc->importData();
        if (data.getData() != IPDataType())
            return data;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return IPData();
}
*/