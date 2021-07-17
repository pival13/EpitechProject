#include <iostream>
#include <QCoreApplication>

#include "../audio/Audio.hpp"
#include "Client.hpp"
#include <chrono>
#include <thread>
#include <QHostInfo>

int main2(int ac, char **av)
{
    try {
        QCoreApplication apk(ac, av);
        std::string ip = "192.168.0.44";
        Client cli(ip, 4242); 
        std::string mail("quentin.felix@epitech.eu"), mdp("bite"), username("HHHH");
        //cli.login(mail, mdp);
        //cli.addFriend(std::string("adrien.heros@epitech.eu"));
        //cli.addMessage(std::string("adrien.heros@epitech.eu"), std::string("j'encule"), 1);

        //cli.addMessage(std::string("quentin.felix@epitech.eu"), std::string("hgzefvcgezsvcgsvcvgzhcvg"), 0);
        //cli.signUp(username, username, username);
          
        /*TCPConnection tcpC(0, ip, 4242);
        tcpC.init();
        tcpC.login(name, pws);

        //Babel::Audio a;
        /*UDPConnection udpC;

        QHostAddress hostList = QHostInfo::fromName(QHostInfo::localHostName()).addresses().front();

        a.sendAudioCallback([&udpC](const std::vector<uint8_t> &data) {
            udpC.sendData(data, ("192.168.43.224"/*"192.168.1.42"), 1234);
        });
        udpC.receiveDataCallback([&a](const std::vector<uint8_t> &data, const std::string &ip, size_t port) {
            a.receiveAudio(data, ip+":"+std::to_string(port));
        });*/
        apk.exec();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}