#include "package_mgr.h"
#include "package_error.h"
#include "packages/comm_package_if.h"
#include <iostream>

int main(int argc, const char* argv[])
{
    packagemgr::packagemgr_instance::instance()->Startup();
    ICommPackage* package;
    packagemgr::PackageError::ErrorType ret = packagemgr::packagemgr_instance::instance()->GetPackage("CommPackage", package);
    if (packagemgr::PackageError::PACKAGE_SUCCESS != ret)
    {
        std::cout << "Get package instance fail: " << ret << std::endl;
        return -1;
    }
    ISocketService* socket_service = package->get_socket_service();
    if (socket_service)
    {
        socket_service->Send(0, 0);
    }
    ISharedMemoryService* shared_memoro_service = package->get_sharedmemory_service();
    if (shared_memoro_service)
    {
        shared_memoro_service->Shmget();
    }

    packagemgr::packagemgr_instance::instance()->Shutdown();


    return 0;
}

