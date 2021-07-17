#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <chrono>
#include <signal.h>
#include <errno.h>

#include "Process.hpp"
#include "PipeIPC.hpp"
#include "../IPC/IPInt.hpp"
#include "../IPC/IPString.hpp"

int main()
{
    PipeIPC ipc;

    Process p([&ipc]() {
        ipc.prepareOtherSide();

        IPInt i(18);
        std::cout << "Fork: Write " << ipc.exportData(IPData(i)) << " bits" << std::endl;
        i = 87643234567876543;
        std::cout << "Fork: Write " << ipc.exportData(IPData(i)) << " bits" << std::endl;
        IPString s("Hello world");
        std::cout << "Fork: Write " << ipc.exportData(IPData(s)) << " bits" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::cout << "Fork: Read " << IPString(ipc.importData().getData()) << std::endl;

        return 0;
    });
    ipc.prepareFirstSide();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    std::cout << "Read " << IPInt(ipc.importData().getData()) << std::endl;
    std::cout << "Read " << IPInt(ipc.importData().getData()) << std::endl;
    std::cout << "Read " << IPString(ipc.importData().getData()) << std::endl;

    IPString s("Hello my children");
    std::cout << "Write " << ipc.exportData(IPData(s)) << " bits" << std::endl;

    std::cout << ipc.isActive() << std::endl;

    p.join();

    std::cout << ipc.isActive() << std::endl;
    return 0;
}