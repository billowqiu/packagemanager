#include "sharedmemory_service.h"
#include <iostream>

SharedMemoryService::SharedMemoryService()
{
    std::cout << __FUNCTION__ << std::endl;
}

SharedMemoryService::~SharedMemoryService()
{
    std::cout << __FUNCTION__ << std::endl;
}

int SharedMemoryService::Shmget()
{
    std::cout << __FUNCTION__ << std::endl;
    return -1;
}

void* SharedMemoryService::Shmat( int id )
{
    std::cout << __FUNCTION__ << std::endl;
    return NULL;
}

int SharedMemoryService::Shmdt( void* addr )
{
    std::cout << __FUNCTION__ << std::endl;
    return -1;
}

bool SharedMemoryService::Initialize()
{
    std::cout << __FUNCTION__ << std::endl;
    return true;
}

bool SharedMemoryService::Finalize()
{
    std::cout << __FUNCTION__ << std::endl;
    return true;
}

