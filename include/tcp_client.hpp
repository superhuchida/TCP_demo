#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <cstdint>

class TcpClient
{
public:
    TcpClient();
    ~TcpClient();

    bool connectTo(const char* address, std::uint16_t port);
    void communicate();

private:
    int socket_fd_;
};

#endif /* TCP_CLIENT_HPP */
