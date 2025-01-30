#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

class TcpServer {
public:
    TcpServer(boost::asio::io_context &io_context, short port);

private:
    void do_accept();

    boost::asio::ip::tcp::acceptor m_acceptor;
};

#endif
