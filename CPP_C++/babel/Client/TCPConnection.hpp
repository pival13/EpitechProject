/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** TCPconnection
*/

#pragma once

//Basic includes
#include <iostream>
#include <string>
#include <cstring>

//Qt5 includes
#include <QtCore/QCoreApplication>
#include <QObject>
#include <QTcpSocket>
#include <QtNetwork>
#include <QDebug>

//Project includes
#include "../libs/lib_client_server.h"
#include "INetwork.hpp"

class ServerCloseException : std::exception {
public:
    ServerCloseException() = default;
    ~ServerCloseException() = default;
    const char *what() { return "Server has closed"; }
};

class TCPConnection: public QObject, public INetwork {
    public:
        void receiveDataCallback(const std::function<void(const std::vector<uint8_t> &, const std::string &, size_t)> &callbackFunction);
        void sendData(const std::vector<uint8_t> &data, const std::string &ip, size_t port);
    Q_OBJECT
    public:
        TCPConnection(QObject *parent = 0, std::string adr = "127.0.0.1", size_t port = 4242);
        ~TCPConnection();

        void createConnection();
        void receive();
        void sendData(qint64 bytes);
        void disconnect();
        bool IsConnected() const;
        void init();

        //get
        QTcpSocket & getTCPSocket() {return socket;};
    
    public slots:
        void connected();
        void disconnected();
        void hostFound();
        void bytesWritten(qint64 bytes);
        void readyRead();
    private:
        QTcpSocket socket;
        std::string addr;
        size_t pport;
    
        std::function<void(const std::vector<uint8_t> &, const std::string &, size_t)> callback;
};