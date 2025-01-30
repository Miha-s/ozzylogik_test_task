#include <iostream>
#include <boost/asio.hpp>
#include "server/tcp_server.hpp"

int main() {
  try {
    boost::asio::io_context io_context;
    TcpServer server(io_context, 2222);
    io_context.run();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
