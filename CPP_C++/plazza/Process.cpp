/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Process
*/

#include "Process.hpp"
#include <cstdlib>

std::list<Process> Process::_processes;

Process::Process(const std::string &cmdLine)
{
    _joinable = false;
    (void)cmdLine;
    /*pid = fork();
    if (pid == -1) {
        _joinable = false;
    } else if (pid == 0) {
        _joinable = true;
    } else {
        std::vector<char *> tbl;
        for (size_t i = 0; i != cmdLine.npos; i = cmdLine.find_first_of(' ', i+1))
            tbl.push_back(cmdLine.substr(i == 0 ? i : i+1, cmdLine.find_first_of(' ', i+1)).data());
        execvp(tbl[0], tbl.data());
    }*/
}

Process::Process(std::function<int()> main)
{
    launchProcess(main);
}

Process::Process(std::function<int(Process &)> main)
{
    launchProcessIPC(main);
}

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
    _ipc.reset();
    for (Process &p : _processes)
        p.detach();
    _processes.clear();

    pid = rhs.pid;
    _joinable = rhs._joinable;
    _ipc = std::move(rhs._ipc);
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