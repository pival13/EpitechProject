/*
** By Kevin Pruvost, May 2020
** ClientSocket.hpp
** File description:
** client socket
*/

#pragma once

#ifndef __USE_XOPEN
#define __USE_XOPEN
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

// Project includes
#include "Exception.hpp"
#include "KVector.hpp"

// C++ includes
#include <thread>

// C includes
#include <stdint.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdbool.h>
#include <netdb.h>
#include <limits.h>
#include <fcntl.h>
#include <uuid/uuid.h>

// Defines
#define CRLF "\r\n\0"
#define IP "127.0.0.1"
#define CLIENT_NUMBER 1024

#undef EXIT_FAILURE
#define EXIT_FAILURE 84
#define EXIT_PASS 42

#define BUFFER_SIZE 1024

bool starts_with(const char *pre, const char *str);
bool ends_with(const char * base, const char * str);
KVector<std::string> splitString(const std::string & str, const std::string & delim);
int hostname_to_ip(char * hostname, char * ip);

/**
 * @brief Socket for Client class.
 */
class ClientSocket
{
public:
    ClientSocket(const char * ip, uint16_t port);
    ~ClientSocket();

    /**
     * @brief Reads the server request and translates it to _lastResponse.
     * @return int
     */
    int readServer();
    /**
     * @brief Returns _lastResponse.
     * @return KVector<std::string>
     */
    KVector<std::string> getLastResponse();
    /**
     * @brief Send a formatted request.
     * @param req
     * @return int
     */
    int sendRequest(std::string req);

private:
    int createFdSet(int distantFd, fd_set * fdSet);
    int readServerResponse();
    int parseServerResponse(const std::string & response);

private:
    KVector<std::string> _lastResponse;

    struct sockaddr_in distantSock;
    int distantFd;
    const char * ip;
    uint16_t port;
    bool error;
};