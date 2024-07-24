#include "LoginServer.h"

namespace net
{
    LoginServer::LoginServer(int port) : TCPServer(port)
    {}

    LoginServer::~LoginServer()
    {}
}