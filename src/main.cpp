#include "net/LoginServer.h"

int main(int argc, char** argv)
{
    net::LoginServer loginServer(8484);
    loginServer.start();
}