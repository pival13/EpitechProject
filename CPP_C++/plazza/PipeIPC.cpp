/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** PipeIPC
*/

#include "PipeIPC.hpp"

PipeIPC::PipeIPC()
{
    if (pipe2(this->__fdFirst, O_NONBLOCK) || pipe2(this->__fdOther, O_NONBLOCK))
        throw std::runtime_error("Failed pipe creation");
    signal(SIGPIPE, SIG_IGN);
}

PipeIPC::~PipeIPC()
{
    close(this->__fdRead);
    close(this->__fdWrite);
}

void PipeIPC::prepareFirstSide()
{
    close(this->__fdFirst[0]);
    close(this->__fdOther[1]);
    this->__fdRead = this->__fdOther[0];
    this->__fdWrite = this->__fdFirst[1];
}

void PipeIPC::prepareOtherSide()
{
    close(this->__fdFirst[1]);
    close(this->__fdOther[0]);
    this->__fdRead = this->__fdFirst[0];
    this->__fdWrite = this->__fdOther[1];
}

bool PipeIPC::isActive() const
{
    size_t size = 0;

    if (write(this->__fdWrite, &size, sizeof(size_t)) != sizeof(size_t))
        return false;
    return true;
}

ssize_t PipeIPC::exportData(const IPData &data)
{
    size_t size = data._data.size();

    write(this->__fdWrite, &size, sizeof(size_t));
    return write(this->__fdWrite, data._data.data(), data._data.size());
}

IPData PipeIPC::importData()
{
    char buffer[sizeof(size_t)];
    size_t bufferSize;
    IPData ipdata;
    int readSize;

    memset(buffer, '\0', sizeof(size_t));
    while (1) {
        readSize = read(this->__fdRead, buffer, sizeof(size_t));
        if (readSize != 8)
            return ipdata;
        bufferSize = *(size_t *)buffer;
        if (bufferSize != 0)
            break;
    }
    ipdata._data.resize(bufferSize);
    read(this->__fdRead, ipdata._data.data(), bufferSize);
    return ipdata;
}
