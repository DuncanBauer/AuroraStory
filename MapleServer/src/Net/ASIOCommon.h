#pragma once

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
class MapleClient;

// Aliases
using byte = unsigned char;
using Connection = std::shared_ptr<MapleClient>; 
using Connections = std::shared_ptr<std::vector<Connection>>;