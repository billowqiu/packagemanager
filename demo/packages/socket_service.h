#ifndef SOCKET_SERVICE_H_
#define SOCKET_SERVICE_H_
#include "comm_package_if.h"
#include "service_entry_if.h"

class SocketService : public ISocketService, public packagemgr::IServiceEntry
{
public:
    SocketService();
    virtual ~SocketService();
    
    virtual void Send(const char* data, uint16_t len);
    virtual void Recv(char* data, uint16_t& len);
    
    virtual bool Initialize();
    virtual bool Finalize();
};

#endif // SOCKET_SERVICE_H_
