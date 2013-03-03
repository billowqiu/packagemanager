#include "socket_service.h"

SocketService::SocketService()
{
}

SocketService::~SocketService()
{
}

void SocketService::Send( const char* data, uint16_t len )
{
}

void SocketService::Recv( char* data, uint16_t& len )
{
}

bool SocketService::Initialize()
{
    return true;
}

bool SocketService::Finalize()
{
    return false;
}
