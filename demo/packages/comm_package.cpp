#include "comm_package.h"
#include "common_define.h"
#include "socket_service.h"
#include "sharedmemory_service.h"
#include <iostream>
using namespace packagemgr;

CommPackage::CommPackage():
socket_service_(NULL),
sharedmemory_service_(NULL)
{
    std::cout << __FUNCTION__ << std::endl;
}

CommPackage::~CommPackage()
{
    delete sharedmemory_service_;
    delete socket_service_;
    std::cout << __FUNCTION__ << std::endl;
}

ISocketService* CommPackage::get_socket_service()
{
    if (socket_service_)
    {
        return socket_service_;
    }
    else
    {
        socket_service_ = new SocketService();
        return socket_service_;
    }
}

ISharedMemoryService* CommPackage::get_sharedmemory_service()
{
    if (sharedmemory_service_)
    {
        return sharedmemory_service_;
    }
    else
    {
        sharedmemory_service_ = new SharedMemoryService();
        return sharedmemory_service_;
    }
}

float CommPackage::Version()
{
    return 0.01f;
}

bool CommPackage::Startup()
{
    return true;
}

bool CommPackage::Shutdown()
{
    return true;
}

std::string CommPackage::Name()
{
    return "CommPackage";
}

void CommPackage::Notify( EPackageNotify type, const void* data )
{
}

PACKAGE_DEFINE(CommPackage)
