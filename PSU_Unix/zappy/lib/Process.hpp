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

///@brief Process handling class
class Process {
    public:
        ///@brief Construct a new Process object with command line. Buffer redirection are not handled.
        ///
        ///@param cmdLine Simple command line use to launch a new process.
        Process(const std::string &cmdLine);
        ///@brief Construct a new Process object with a main function.
        ///
        ///@param main Main function which will be execute on the new process.
        Process(std::function<int()> main);
        ///@brief Construct a new Process object with a main function and its arguments.
        ///
        ///@param main Main function which will be execute on the new process.
        ///@param argc Argc parameter passed to \@main.
        ///@param argv Argv parameter passed to \@main.
        Process(std::function<int(int,char*[])> main, int argc, char *argv[]);
        ///@brief Construct a new Process object with a main function and its arguments.
        ///
        ///@param main Main function which will be execute on the new process.
        ///@param argc Argc parameter passed to \@main.
        ///@param argv Argv parameter passed to \@main.
        ///@param env Env parameter passed to \@main.
        Process(std::function<int(int,char*[],char*[])> main, int argc, char *argv[], char *env[]);

        Process() {}
        Process(const Process &) = delete;
        Process(Process &&p);
        ~Process();

        Process &operator=(const Process &) = delete;
        Process &operator=(Process &&rhs);

        ///@brief Wait until the process execution has ended.
        ///
        ///@return The return value of the process.
        int join();
        ///@brief Detaches the process represented by the object.
        ///@details Allow processes to execute independently from each other.
        ///
        ///Both processes continue without blocking nor synchronizing in any way. Note that when either one ends execution, its resources are released.
        ///
        ///After a call to this function, the Process object becomes non-joinable and can be destroyed safely.
        ///
        void detach();
        ///@brief Get pid of the childs process.
        ///
        ///@return The pid of the child process.
        inline int getPid() const { return pid == 0? parentPid: pid; }
        ///@brief Returns whether the process object is joinable.
        ///@details A Process is joinable if it represents another process.
        ///
        ///A Process is not joinable in any of these cases:
        /// * if it was default-constructed.
        /// * if it has been moved from (either constructing another Process, or assigning to it).
        /// * if either of its members `join()` or `detach()` has been called. 
        inline bool joinable() const { return _joinable; }
        ///@brief Check whether the current process is the one that create Process.
        ///@details This is only useful when using an `IPC Process`. In this case, two processes can communicate with a `Process`. As this is not implements yet, this will always return True.
        ///
        ///@return True
        inline bool isParent() const { return pid != 0; }

    private:
        void launchProcess(std::function<int()> main);

        int pid;
        int parentPid;
        bool _joinable = false;
        static std::list<Process> _processes;
};
