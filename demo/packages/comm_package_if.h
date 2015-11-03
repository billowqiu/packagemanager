#ifndef COMM_PACKAGE_IF_H_
#define COMM_PACKAGE_IF_H_
#include <stdint.h>
#include "common_define.h"

interface ICommPackage;
interface ISocketService;
interface ISharedMemoryService;

interface ICommPackage
{
    virtual ISocketService* get_socket_service() = 0;
    virtual ISharedMemoryService* get_sharedmemory_service() = 0;
};

interface ISocketService
{
    virtual ~ISocketService() {}
    virtual void Send(const char* data, uint16_t len) = 0;
    virtual void Recv(char* data, uint16_t& len) = 0;
};

interface ISharedMemoryService
{
    virtual ~ISharedMemoryService() {}
    virtual int Shmget() = 0;
    virtual void* Shmat(int id) = 0;
    virtual int Shmdt(void* addr) = 0;
};

#endif // COMM_PACKAGE_IF_H_
