#ifndef LOGGING_UTILS_HPP
#define LOGGING_UTILS_HPP

#include <boost/asio.hpp>
#include <ostream>

void log_error(const boost::asio::ip::tcp::endpoint &endpoint,
               const boost::system::error_code ec,
               const std::string &info = "");

void log_info(const boost::asio::ip::tcp::endpoint &endpoint,
              const std::string &info = "");

std::ostream& operator<<(std::ostream& os, const boost::asio::ip::tcp::endpoint& endpoint);

#endif
