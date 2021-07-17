/*
** EPITECH PROJECT, 2020
** Client
** File description:
** UDPConnection
*/

#include "UDPConnection.hpp"

UDPConnection::UDPConnection(QObject *parent) :
    QObject(parent), socket(this)
{
    if (!socket.bind(1234))
        if (!socket.bind())
            throw std::runtime_error("Bind failed: " + std::string(socket.errorString().toUtf8().constData()));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    qDebug() << "local port : " << socket.localPort();
    port = socket.localPort();

    /*const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses())
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            ip = address.toString().toUtf8().data();
            return;
        }
    */
    //audio.sendAudioCallback([this](const std::vector<uint8_t> &data) {
    //    audio_data = data;
    //    SayHello();
    //});
    
}

UDPConnection::~UDPConnection()
{
}

void UDPConnection::sendData(const std::vector<uint8_t> &data, const std::string &ip, size_t port)
{
    QByteArray data_array = QByteArray::fromRawData((const char *)data.data(), int(data.size()));
    socket.writeDatagram(data_array, QHostAddress(ip.data()), uint16_t(port));
}

void UDPConnection::receiveDataCallback(const std::function<void(const std::vector<uint8_t> & data, const std::string & ip, size_t port)> &callbackFunction)
{
    callback = callbackFunction;
}

void UDPConnection::SayHello()
{
    if (audio_data.size() == 0)
        return;
    sendData(audio_data, "127.0.0.1", 1234);
    audio_data.clear();
}

void UDPConnection::readyRead()
{
    QByteArray buffer;
    buffer.resize(socket.pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socket.readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    static bool b = false;
    if (!b) {
        //qDebug() << "Connected to " << sender.toString() << ":" << senderPort;
        //qDebug() << "Message: " << buffer;
        b = true;
    }

    const void *data = buffer;
    std::vector<uint8_t> a ((char *)data, ((char *)data) + buffer.size()); 

    if (callback)
        callback(a, std::string(sender.toString().toUtf8().constData()), size_t(senderPort));
    //audio.receiveAudio(a, std::string(sender.toString().toUtf8().constData())+":"+std::to_string(senderPort));
}