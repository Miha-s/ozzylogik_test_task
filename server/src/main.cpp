#include <iostream>
#include <boost/asio.hpp>
#include "server/tcp_server.hpp"

void run_server(int port) {
    boost::asio::io_context io_context;
    TcpServer server(io_context, port);
    io_context.run();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    int port = std::stoi(argv[1]);
    if (port <= 0 || port > 65535) {
        std::cerr << "Invalid port number. Please provide a value between 1 and 65535." << std::endl;
        return 1;
    }

    try {
        run_server(port);
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
    }

    return 0;
}
