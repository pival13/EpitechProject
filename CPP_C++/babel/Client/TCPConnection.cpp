/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Client
*/

#include "TCPConnection.hpp"

TCPConnection::TCPConnection(QObject *parent, std::string adr, size_t port) : 
    QObject( parent ),
    socket ( this ),
    addr ( adr ),
    pport ( port )
{
    init();
}

TCPConnection::~TCPConnection()
{
    socket.close();
}

void TCPConnection::sendData(const std::vector<uint8_t> &data, const std::string &ip, size_t port)
{
    socket.write((char *)data.data(), data.size());
}


void TCPConnection::init()
{
    connect(&socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(&socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&socket, SIGNAL(hostFound()), this, SLOT(hostFound()));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "Connecting...";

    socket.connectToHost(QString(addr.data()), pport);

    if (!socket.waitForConnected(3000)) {
        qDebug() << "Error " << socket.errorString();
        throw std::runtime_error("No server available");
    }
    qDebug() << "le wait est terminé";
}

void TCPConnection::connected()
{
    qDebug() << "Connected!";
}

void TCPConnection::disconnected()
{
    qDebug() << "Disconnected!";
}

void TCPConnection::hostFound()
{
    qDebug() << "hostFound";
}

void TCPConnection::bytesWritten(qint64 bytes)
{
    qDebug() << "we wrote: " << bytes;
    if (socket.isWritable()) {
        //socket.write("Ma bite!\n");
        socket.waitForBytesWritten();
    }
}

void TCPConnection::receiveDataCallback(const std::function<void(const std::vector<uint8_t> &, const std::string &, size_t)> &callbackFunction)
{
    callback = callbackFunction;
}

void TCPConnection::readyRead()
{
    qDebug() << "Reading...";

    char *buffer = NULL;
    QByteArray data;

    data = socket.readAll();
    //qDebug() << data;

    std::vector<uint8_t> a (data.data(), (data.data()) + data.size()); 
    if (callback)
        callback(a, std::string(this->addr), this->pport);
}

void TCPConnection::disconnect()
{
    qDebug() << "Deconnexion";
}

bool TCPConnection::IsConnected() const
{
    return socket.state() == QAbstractSocket::ConnectedState;
}