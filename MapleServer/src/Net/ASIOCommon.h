#ifndef ASIOCOMMON_H
#define ASIOCOMMON_H

// C++
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

// Boost
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

// Namespaces
using boost::asio::ip::tcp;

// Forward Declarations
class TCPConnection;

// Aliases
using byte = unsigned char;
using ByteBuffer = std::vector<byte>;
using Connection = std::shared_ptr<TCPConnection>; 
using Connections = std::shared_ptr<std::vector<Connection>>;

#endif