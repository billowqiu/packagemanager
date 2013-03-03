#include "sharedmemory_service.h"

SharedMemoryService::SharedMemoryService()
{
}

SharedMemoryService::~SharedMemoryService()
{
}

int SharedMemoryService::Shmget()
{
    return -1;
}

void* SharedMemoryService::Shmat( int id )
{
    return NULL;
}

int SharedMemoryService::Shmdt( void* addr )
{
    return -1;
}

bool SharedMemoryService::Initialize()
{
    return true;
}

bool SharedMemoryService::Finalize()
{
    return true;
}
