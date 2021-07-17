/*
** EPITECH PROJECT, 2020
** Client
** File description:
** UDPConnection
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <QObject>
#include <QUdpSocket>
#include <QDebug>
#include <QNetworkInterface>
#include <QHostInfo>

#include "../audio/Audio.hpp"
#include "INetwork.hpp"

class UDPConnection : public QObject, public INetwork {
    Q_OBJECT
    public:
        explicit UDPConnection(QObject *parent = 0);
        ~UDPConnection();
        
        void SayHello();
        void sendData(const std::vector<uint8_t> &data, const std::string &ip, size_t port);
        void receiveDataCallback(const std::function<void(const std::vector<uint8_t> &, const std::string &, size_t)> &callbackFunction);

        std::vector<uint8_t> audio_data;
        //const std::string & getUdpIp() {return ip;};
        const short getUdpPort() {return port;};
        //Babel::Audio audio;
    public slots:
        void readyRead();
    private:
        std::function<void(const std::vector<uint8_t> &, const std::string &, size_t)> callback;
        QUdpSocket socket;
        //std::string ip;
        short port;
};