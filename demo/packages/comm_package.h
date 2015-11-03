#ifndef COMM_PACKAGE_H_
#define COMM_PACKAGE_H_
#include "comm_package_if.h"
#include "package_if.h"

class CommPackage : public ICommPackage, public packagemgr::IPackage
{
public:
    CommPackage();
    ~CommPackage();

    virtual ISocketService* get_socket_service();
    virtual ISharedMemoryService* get_sharedmemory_service();

	virtual float Version();
    virtual bool Startup();
    virtual bool Shutdown();
	virtual std::string Name();
    virtual void Notify(packagemgr::EPackageNotify type, const void* data);

private:
    ISocketService* socket_service_;
    ISharedMemoryService* sharedmemory_service_;
};

#endif // COMM_PACKAGE_H_

