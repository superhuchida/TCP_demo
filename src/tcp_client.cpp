#include "tcp_client.hpp"
#include "tcp_common.hpp"

#include <cstring>
#include <iostream>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

TcpClient::TcpClient()
    : socket_fd_(-1)
{
}

TcpClient::~TcpClient()
{
    if (socket_fd_ >= 0)
    {
        (void)close(socket_fd_);
    }
}

bool TcpClient::connectTo(const char* address, std::uint16_t port)
{
    socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd_ < 0)
    {
        return false;
    }

    sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, address, &server_addr.sin_addr) <= 0)
    {
        return false;
    }

    if (connect(socket_fd_,
                reinterpret_cast<sockaddr*>(&server_addr),
                sizeof(server_addr)) < 0)
    {
        return false;
    }

    return true;
}

void TcpClient::communicate()
{
    const char message[] = "Hello from TCP client";
    (void)send(socket_fd_, message, sizeof(message), 0);

    char buffer[BUFFER_SIZE] {};
    ssize_t received = recv(socket_fd_, buffer, sizeof(buffer) - 1U, 0);

    if (received > 0)
    {
        std::cout << "Client received: " << buffer << std::endl;
    }
}
