#ifndef SERVICE_ENTRY_IF_H
#define SERVICE_ENTRY_IF_H

#include "common_define.h"
namespace packagemgr
{

interface IServiceEntry
{
    virtual ~IServiceEntry()
    {
    }
	/** 
	 *  服务初始化/销毁
	 *  @return 成功或者失败.
	*/
	virtual bool Initialize() = 0;
	virtual bool Finalize() = 0;
};

}

#endif // SERVICE_ENTRY_IF_H
