#include "session.hpp"

#include <boost/asio.hpp>

#include "algorithm/json_convertor.hpp"
#include "algorithm/words_counter.hpp"
#include "logging/utils.hpp"

using boost::asio::ip::tcp;

Session::Session(tcp::socket socket) : m_socket(std::move(socket)) {}

void Session::start() { read_header(); }

void Session::read_header() {
  auto self(shared_from_this());
  boost::asio::async_read(
      m_socket, boost::asio::buffer(&m_msg_size, sizeof(m_msg_size)),
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
          m_msg_size = ntohl(m_msg_size);
          read_message();
        }
        else if(ec  == boost::asio::error::eof) {
          log_info(m_socket.remote_endpoint(), "User closed connection");
        } else {
          log_error(m_socket.remote_endpoint(), ec, "Error reading header");
        }
      });
}

void Session::read_message() {
  auto self(shared_from_this());
  m_buffer.resize(m_msg_size);
  boost::asio::async_read(
      m_socket, boost::asio::buffer(m_buffer),
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
          process();
        } else {
          log_error(m_socket.remote_endpoint(), ec, "Error reading message");
        }
      });
}

void Session::process() {
  WordsCounter counter(m_buffer);

  counter.process();
  m_response = convert_to_json(counter.get_result());
  log_info(m_socket.remote_endpoint(), "User text processed");

  write_header();
}

void Session::write_header() {
  auto self(shared_from_this());

  m_response_size = htonl(m_response.size());

  boost::asio::async_write(
      m_socket, boost::asio::buffer(&m_response_size, sizeof(m_response_size)),
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
          write_response();
        } else {
          log_error(m_socket.remote_endpoint(), ec, "Error sending header");
        }
      });
}

void Session::write_response() {
  auto self(shared_from_this());

  boost::asio::async_write(
      m_socket, boost::asio::buffer(m_response),
      [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
          start();
        } else {
          log_error(m_socket.remote_endpoint(), ec, "Error sending JSON data");
        }
      });
}
