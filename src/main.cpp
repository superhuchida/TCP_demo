#include "tcp_server.hpp"
#include "tcp_client.hpp"
#include "tcp_common.hpp"

#include <iostream>
#include <cstring>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: ./tcp_example [server|client]\n";
        return 1;
    }

    if (std::strcmp(argv[1], "server") == 0)
    {
        TcpServer server;
        if (server.start(TCP_PORT))
        {
            std::cout << "Server running...\n";
            server.run();
        }
    }
    else if (std::strcmp(argv[1], "client") == 0)
    {
        TcpClient client;
        if (client.connectTo("127.0.0.1", TCP_PORT))
        {
            client.communicate();
        }
    }

    return 0;
}
