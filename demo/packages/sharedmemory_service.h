#ifndef SHAREDMEMORY_SERVICE_H_
#define SHAREDMEMORY_SERVICE_H_
#include "comm_package_if.h"
#include "service_entry_if.h"

class SharedMemoryService : public ISharedMemoryService, public packagemgr::IServiceEntry
{
public:
    SharedMemoryService();
    virtual ~SharedMemoryService();

    virtual int Shmget();
    virtual void* Shmat(int id);
    virtual int Shmdt(void* addr);

    virtual bool Initialize();
    virtual bool Finalize();
};

#endif // SHAREDMEMORY_SERVICE_H_

