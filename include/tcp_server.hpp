#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <cstdint>

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();

    bool start(std::uint16_t port);
    void run();

private:
    int server_fd_;
    int client_fd_;
};

#endif /* TCP_SERVER_HPP */
