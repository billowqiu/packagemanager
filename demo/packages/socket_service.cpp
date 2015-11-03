#include "socket_service.h"
#include <iostream>

SocketService::SocketService()
{
    std::cout << __FUNCTION__ << std::endl;
}

SocketService::~SocketService()
{
    std::cout << __FUNCTION__ << std::endl;
}

void SocketService::Send( const char* data, uint16_t len )
{
    std::cout << __FUNCTION__ << std::endl;
}

void SocketService::Recv( char* data, uint16_t& len )
{
    std::cout << __FUNCTION__ << std::endl;
}

bool SocketService::Initialize()
{
    std::cout << __FUNCTION__ << std::endl;
    return true;
}

bool SocketService::Finalize()
{
    std::cout << __FUNCTION__ << std::endl;
    return false;
}
