#include "utils.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &os,
                         const boost::asio::ip::tcp::endpoint &endpoint) {
  os << endpoint.address().to_string() << ":" << endpoint.port();
  return os;
}

void log_error(const boost::asio::ip::tcp::endpoint &endpoint,
               const boost::system::error_code ec, const std::string &info) {
  std::cerr << endpoint << " - " << (info.empty() ? "" : info + ": ")
            << ec.to_string() << std::endl;
}

void log_info(const boost::asio::ip::tcp::endpoint &endpoint,
              const std::string &info) {
  std::cout << endpoint << " - " << info << std::endl;
}
