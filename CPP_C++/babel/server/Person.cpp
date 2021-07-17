/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** TcpConnection
*/

#include "Person.hpp"

Person::Person(boost::asio::io_context& ioc,
    boost::asio::io_context::strand& strand, ChatRoom& room,
    const std::string & dbPath)
    : m_context (ioc),
    m_socket(ioc),
    m_strand (strand),
    m_room (room),
    m_dbPath(dbPath)
{
    this->m_uuid = {00000000-0000-0000-0000-000000000000};
}

Person::~Person()
{
    std::cout << "delete" << std::endl;
}

Person::pointer Person::create(boost::asio::io_context& ioc,
    boost::asio::io_context::strand& strand, ChatRoom& room,
    const std::string & dbPath)
{
    return pointer(new Person(ioc, strand, room, dbPath));
}

tcp::socket& Person::socket()
{
    return this->m_socket;
}

void Person::start()
{
    this->m_room.enter(shared_from_this());
    this->m_ip = this->m_socket.remote_endpoint().address().to_string();
    doRead();
}

std::string Person::getIp()
{
    return this->m_ip;
}

short Person::getPort()
{
    return this->m_port;
}

void Person::setUuid(boost::uuids::uuid uuid)
{
    this->m_uuid = uuid;
}

boost::uuids::uuid Person::getUUid() const
{
    return this->m_uuid;
}

void Person::WriteStatusBuffer(WriteMessage writeMessage)
{
    boost::asio::async_write(this->m_socket,
        boost::asio::buffer(writeMessage.getData(),
            writeMessage.getLength()),
        this->m_strand.wrap(
            [this](const boost::system::error_code& ec, std::size_t size) {
                if (ec) {
                    std::cerr << "Error write" << std::endl;
                    this->m_room.leave(shared_from_this());
                } else {
                    std::cout << size << " bytes send" << std::endl;;
                }
            }
        )
    );
}

void Person::runCommand()
{
    header_t header = this->readMessage.getHeader();

    if (header.func == LOGIN) {
        WriteMessage LoginMessage;
        Login login(readMessage, LoginMessage, this->m_mail, this->m_port, this->m_dbPath);
        login.getAnswer();
        if (!this->m_mail.empty()) {
            NewStatus status(this->readMessage, this->m_room, LOGIN, this->m_mail, this->m_dbPath);
            status.updateStatus(ONLINE, this->m_mail);
            status.notificationStatus();
        }
        writeBuffer.push_back(LoginMessage);
    } else if (header.func == SIGN_UP) {
        WriteMessage WriteMessage;
        Signup signup(readMessage, WriteMessage, this->m_mail, this->m_port, this->m_dbPath);
        signup.getAnswer();
        writeBuffer.push_back(WriteMessage);
    } else if (header.func == ADD_FRIEND) {
        WriteMessage addFriendMessage;
        AddFriend addFriend(this->readMessage, addFriendMessage, this->m_mail, this->m_dbPath);
        addFriend.getAnswer();
        this->writeBuffer.push_back(addFriendMessage);
    } else if (header.func == DELETE_FRIEND) {
        WriteMessage deleteFriendMessage;
        DeleteFriend deleteFriend(this->readMessage, deleteFriendMessage, this->m_mail, this->m_dbPath);
        deleteFriend.getAnswer();
        this->writeBuffer.push_back(deleteFriendMessage);
    } else if (header.func == NEW_STATUS) {
        NewStatus status(this->readMessage, this->m_room, NEW_STATUS, this->m_mail, this->m_dbPath);
        status.getAnswer();
    } else if (header.func == MESSAGE) {
        WriteMessage message;
        Message messageObj(this->readMessage, message, this->m_mail, this->m_room, this->m_dbPath);
        messageObj.getAnswer();
        this->writeBuffer.push_back(message);
    } else if (header.func == DISCONNECT) {
        Disconnect disconnect(this->readMessage, this->m_mail, this->m_room, this->m_dbPath);
        disconnect.getAnswer();
        this->m_mail.clear();
    } else if (header.func == GET_CONTACT_MESSAGE) {
        WriteMessage message;
        GetContactMessage getContactMessage(this->readMessage, message, this->m_mail, this->m_dbPath);
        getContactMessage.getAnswer();
        this->writeBuffer.push_back(message);
    } else if (header.func == CALL) {
        Call call(this->readMessage, this->m_ip, this->m_port, this->m_room, this->m_mail, this->m_uuid);
        call.sendRequest();
    } else if (header.func == ACCEPT_CALL || header.func == REFUSE_CALL) {
        Call call(this->readMessage, this->m_ip, this->m_port, this->m_room, this->m_mail, this->m_uuid);
        try {
            call.sendAnswer(header.func);
        } catch(const std::exception & err) {
            std::cout << err.what() << std::endl;
        }
    } else if (header.func == END_CALL) {
        Call call(this->readMessage, this->m_ip, this->m_port, this->m_room, this->m_mail, this->m_uuid);
        try {
            call.leftCall();
        } catch (const std::exception & err) {
            std::cout << err.what() << std::endl;
        }
    }
    if (!this->writeBuffer.empty())
        doWrite();
    else
        doRead();
}

void Person::doRead()
{
    boost::asio::async_read_until(this->m_socket, this->buffer, "\r\n",
        this->m_strand.wrap(
            [this](boost::system::error_code ec, std::size_t size) {
                if (!ec) {
                    std::vector<char> buff(size + 1);
                    std::istream is(&this->buffer);
                    is.readsome(buff.data(), size);

                    this->readMessage.addCommand(buff);
                    this->runCommand();
                } else {
                    std::cerr << "Read error has occured" << std::endl;
                    NewStatus status(this->readMessage, this->m_room, LOGIN, this->m_mail, this->m_dbPath);
                    status.updateStatus(OFFLINE, this->m_mail);
                    status.notificationStatus();
                    this->m_room.leave(shared_from_this());
                }
            }
        )
    );
}

void Person::doWrite()
{
    boost::asio::async_write(this->m_socket,
        boost::asio::buffer(writeBuffer.front().getData(),
            writeBuffer.front().getLength()),
        this->m_strand.wrap(
            [this](const boost::system::error_code& ec, std::size_t size) {
                if (ec) {
                    std::cerr << "Error write" << std::endl;
                    this->m_room.leave(shared_from_this());
                } else {
                    std::cout << size << " bytes send" << std::endl;
                    this->writeBuffer.pop_back();
                    if (!this->writeBuffer.empty())
                        doWrite();
                    else
                        doRead();
                }
            }
        )
    );
}

std::string Person::getParticipantMail()
{
    return this->m_mail;
}

void Person::close()
{
    this->m_socket.close();
}
