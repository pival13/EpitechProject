/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** IPCTest
*/

#include "IPC/IIPC.hpp"
#include <iostream>
#include <unistd.h>

#include "Process.hpp"
#include "IPC/IPString.hpp"
#include "IPC/IPInt.hpp"

int main()
{
    Process p;
    p = Process([](Process &p) {
        IPInt a(18);
        p.sendData(a);
        a = 500;
        p.sendData(a);
        IPString s("Toto");
        p.sendData(s);
        p.sendData(a);
        s = "Hello world";
        p.sendData(s);
        return 0;
    });
    for (int i = 0; i != 5; i++) {
        IPData data = p.receiveData();
        if (data.isType(typeid(IPInt)))
            std::cout << IPInt(data.getData()) << std::endl;
        else if (data.isType(typeid(IPString)))
            std::cout << IPString(data.getData()) << std::endl;
        else
            std::cerr << "Unknow kind of object receive" << std::endl;
    }
    p.join();
}