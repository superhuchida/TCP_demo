#include "tcp_server.hpp"
#include "tcp_common.hpp"

#include <cstring>
#include <iostream>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

TcpServer::TcpServer()
    : server_fd_(-1),
      client_fd_(-1)
{
}

TcpServer::~TcpServer()
{
    if (client_fd_ >= 0)
    {
        (void)close(client_fd_);
    }
    if (server_fd_ >= 0)
    {
        (void)close(server_fd_);
    }
}

bool TcpServer::start(std::uint16_t port)
{
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ < 0)
    {
        return false;
    }

    sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd_,
             reinterpret_cast<sockaddr*>(&server_addr),
             sizeof(server_addr)) < 0)
    {
        return false;
    }

    if (listen(server_fd_, 1) < 0)
    {
        return false;
    }

    return true;
}

void TcpServer::run()
{
    sockaddr_in client_addr {};
    socklen_t client_len = sizeof(client_addr);

    client_fd_ = accept(server_fd_,
                        reinterpret_cast<sockaddr*>(&client_addr),
                        &client_len);

    if (client_fd_ < 0)
    {
        return;
    }

    char buffer[BUFFER_SIZE] {};
    ssize_t received = recv(client_fd_, buffer, sizeof(buffer) - 1U, 0);

    if (received > 0)
    {
        std::cout << "Server received: " << buffer << std::endl;

        const char response[] = "Hello from TCP server";
        (void)send(client_fd_, response, sizeof(response), 0);
    }
}
