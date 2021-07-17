/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** PipeIPC
*/

#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <chrono>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "IPC/IIPC.hpp"

class PipeIPC : public IIPC {
    public:
        PipeIPC();
        ~PipeIPC();

        void prepareFirstSide();
        void prepareOtherSide();

        bool isActive() const;

        ssize_t exportData(const IPData &data);

        IPData importData();
    private:
        int __fdFirst[2] = {0};
        int __fdOther[2] = {0};
        int __fdRead = 0;
        int __fdWrite = 0;
};