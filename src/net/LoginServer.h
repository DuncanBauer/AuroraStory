#pragma once

#include "TCPServer.h"

namespace net
{
    class LoginServer : public TCPServer
    {
    public:
        LoginServer(int port);
        ~LoginServer();
    };
}
