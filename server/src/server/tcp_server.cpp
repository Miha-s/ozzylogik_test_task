#include "tcp_server.hpp"

#include <iostream>

#include "logging/utils.hpp"
#include "session.hpp"

using boost::asio::ip::tcp;

TcpServer::TcpServer(boost::asio::io_context &io_context, short port)
    : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {
  log_info(m_acceptor.local_endpoint(), "Server listens for connection");
  do_accept();
}

void TcpServer::do_accept() {
  m_acceptor.async_accept(
      [this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
          log_info(socket.remote_endpoint(), "New connection");
          std::make_shared<Session>(std::move(socket))->start();
        }
        do_accept();
      });
}
