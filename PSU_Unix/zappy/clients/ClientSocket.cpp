/*
** By Kevin Pruvost, May 2020
** ClientSocket.hpp
** File description:
** client
*/

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(const char * ipp, uint16_t pport)
    : ip { ipp }
    , port { pport }
{
    distantFd = 0;
    error = true;

    distantFd = socket(AF_INET, SOCK_STREAM, 0);
    if (distantFd < 0)
        throw EXCEPTION("socket() error. Cannot connect to the server.");
    bzero(&(distantSock), sizeof(distantSock));
    distantSock.sin_family = AF_INET;
    char * hostname = const_cast<char *>(ipp);
    char ip[100] = {0};
    if (hostname_to_ip(hostname, ip) == EXIT_FAILURE)
        strcpy(ip, hostname);
    if (inet_aton(ip, (struct in_addr *)&(distantSock.sin_addr.s_addr)) == 0)
        throw EXCEPTION("inet_aton() error. Cannot connect to the server.");
    distantSock.sin_port = htons(port);
    if (connect(distantFd, (struct sockaddr *)&(distantSock), sizeof(distantSock)) != 0)
        throw EXCEPTION("connect() error. Cannot connect to the server.");
    error = false;
}

ClientSocket::~ClientSocket()
{
    if (distantFd != 0)
        close(distantFd);
}

KVector<std::string> ClientSocket::getLastResponse()
{
    return _lastResponse;
}

int ClientSocket::createFdSet(int distantFd, fd_set * fdSet)
{
    int fd_max = distantFd;

    FD_ZERO(fdSet);
    FD_SET(distantFd, fdSet);
    return fd_max;
}

int ClientSocket::readServerResponse()
{
    char buffer[BUFFER_SIZE] = {0};
    std::string totalBuffer;
    ssize_t ret = BUFFER_SIZE;
    const char * delimiter = std::string("\n").c_str();

    while (ret > 0 && !ends_with(totalBuffer.c_str(), delimiter))
    {
        memset(buffer, 0, BUFFER_SIZE);
        if ((ret = read(distantFd, buffer, BUFFER_SIZE - 1)) <= 0)
            return EXIT_FAILURE;
        totalBuffer += buffer;
    }

    if (parseServerResponse(totalBuffer) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int ClientSocket::readServer()
{
    fd_set fdSet;
    int fd_max = createFdSet(distantFd, &fdSet);
    struct timeval tv = {1, 0};
    int ret = 0;

    if ((ret = select(fd_max + 1, &fdSet, NULL, NULL, &tv)) < 0)
        return EXIT_FAILURE;
    if (ret == 0)
        return EXIT_PASS;
    if (FD_ISSET(distantFd, &fdSet)) {
        return readServerResponse();
    }
    return EXIT_FAILURE;
}

int ClientSocket::parseServerResponse(const std::string & response)
{
    std::string str;

    for (size_t i = 0; i < response.size(); ++i)
    {
        if (response[i] == '\n')
            str += " \n ";
        else
            str += response[i];
    }
    _lastResponse = splitString(str, " ");
    //std::cout << getpid() << " [SERVER]: " << _lastResponse << std::endl;
    return EXIT_SUCCESS;
}

int ClientSocket::sendRequest(std::string req)
{
    if (req.size() == 0)
        return EXIT_SUCCESS;

    if (req.at(req.size() - 1) != '\n')
        req += "\n";

    fd_set fdSet;
    int fd_max = createFdSet(distantFd, &fdSet);
    struct timeval tv = {1, 0};
    int ret = 0;

    if ((ret = select(fd_max + 1, NULL, &fdSet, NULL, &tv)) < 0)
        return EXIT_FAILURE;

    //std::cout << getpid() << " [CLIENT]: " << req << std::endl;
    while (write(distantFd, req.c_str(), req.size()) <= 0);

    return EXIT_SUCCESS;
}

// TOOLS -----------------------------------------------------------------------

KVector<std::string> splitString(const std::string & str, const std::string & delim)
{
    KVector<std::string> cont;
    std::string temp = str;

    while (!temp.empty()) {
        if (temp.find(delim) == std::string::npos)
            break;
        cont.emplace_back(temp.substr(0, temp.find(delim)));
        temp = temp.substr(temp.find(delim) + delim.size());
    }
    if (!temp.empty())
        cont.emplace_back(temp);
    return cont;
}

bool starts_with(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre);
    size_t lenstr = strlen(str);

    return lenstr > lenpre ? false : memcmp(pre, str, lenstr) == 0;
}

bool ends_with(const char * base, const char * str)
{
    int blen = (base == NULL) ? 0 : strlen(base);
    int slen = (str == NULL) ? 0 : strlen(str);

    if (base == NULL || str == NULL)
        return false;
    if (slen > blen)
        return false;
    return (0 == strcmp(base + blen - slen, str));
}

int hostname_to_ip(char * hostname, char * ip)
{
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	if ( (he = gethostbyname( hostname ) ) == NULL)
	{
		// get the host info
		herror("gethostbyname");
		return EXIT_FAILURE;
	}

	addr_list = (struct in_addr **)he->h_addr_list;

	for(i = 0; addr_list[i] != NULL; ++i)
	{
		//Return the first one;
		strcpy(ip, inet_ntoa(*addr_list[i]));
		return EXIT_SUCCESS;
	}
	return 1;
}