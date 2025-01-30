#ifndef SESSION_HPP
#define SESSION_HPP
#include <boost/asio/ip/tcp.hpp>
#include <memory>

class Session : public std::enable_shared_from_this<Session> {
public:
  Session(boost::asio::ip::tcp::socket socket);

  void start();

private:
  void read_header();
  void read_message();

  void process();

  void write_header();
  void write_response();

  boost::asio::ip::tcp::socket m_socket;
  std::string m_buffer;
  std::string m_response;
  uint32_t m_response_size;
  uint32_t m_msg_size;
};

#endif
