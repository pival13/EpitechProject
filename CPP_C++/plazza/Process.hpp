/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Process
*/

#pragma once

#include <memory>
#include <functional>
#include <iostream>
#include <list>
#include <system_error>

#include <unistd.h>
#include <sys/wait.h>

#include "PipeIPC.hpp"
#include "IPC/IPInt.hpp"
#include "IPC/IPString.hpp"

class Process {
    public:
        Process(const std::string &cmdLine);
        Process(std::function<int()>);
        Process(std::function<int(Process &)>);
        Process(std::function<int(int,char*[])>, int argc, char *argv[]);
        Process(std::function<int(int,char*[],char*[])>, int argc, char *argv[], char *env[]);

        Process() = default;
        Process(const Process &) = delete;
        Process(Process &&p);
        ~Process();

        Process &operator=(const Process &) = delete;
        Process &operator=(Process &&rhs);

        int join();
        void detach();
        inline int getPid() const { return pid == 0? parentPid: pid; }
        inline bool joinable() const { return _joinable; }
        inline bool isParent() const { return pid != 0; }

        inline bool isAlive() const { return _ipc->isActive(); }
        inline bool sendData(IPObject &obj) { return _ipc->exportData(IPData(obj)); }
        IPData receiveData();
        IPData tryReceiveData() { try { return _ipc->importData(); } catch (const std::exception &) { return IPData(); } }

    private:
        void launchProcess(std::function<int()> main);
        void launchProcessIPC(std::function<int(Process &)> main);

        int pid;
        int parentPid;
        std::unique_ptr<IIPC> _ipc;
        bool _joinable = false;
        static std::list<Process> _processes;
};

//operator<</>>