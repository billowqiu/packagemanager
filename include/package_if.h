/********************************************************************
	filename:	package_if.h
	author:		billowqiu
	purpose:	package类似java中包(jar)的概念，一个包表示windows下dll或者linux下面的so
				package开发者必须严格按照接口的方式进行编码，在c++中即表现为virtual函数对外提供服务
				每一个package对外提供的服务都由其接口文件进行定义，当管理器加载package时会调用预定义的导出函数
				具体参加common_define.h文件中的PACKAGE_LOAD和PACKAGE_UNLOAD函数原型
				可以通过宏PACKAGE_DEFINE定义导出函数
*********************************************************************/

#ifndef IPACKAGE_H_
#define IPACKAGE_H_

#include "common_define.h"

namespace packagemgr
{

enum EPackageNotify
{
	NOTIFY_PACKAGE_LOAD,
	NOTIFY_PACKAGE_UNLOAD,
	NOTIFY_PACKAGE_UPDATE
};

interface IPackage
{
	friend class PackageManager;
	struct PackageInfo
	{
		PackageInfo(){}
		PackageInfo(package_handler handle, PACKAGE_LOAD load_fun, PACKAGE_UNLOAD unload_fun):
		m_handle(handle),
		m_packageLoad(load_fun),
		m_packageUnload(unload_fun)
		{
		}
		//包对应的平台相关的句柄
		package_handler m_handle;
		//包加载时由管理器调用的加载函数
		PACKAGE_LOAD m_packageLoad;
		//包卸载时由管理器调用的卸载函数
		PACKAGE_UNLOAD m_packageUnload;
	};

public:
	virtual ~IPackage()
    {
    }

	/** 
	 *  包的版本
	 *  @return float.
	*/
	virtual float Version() = 0;

    /** 
     *  包启动/停止
     *  @return bool.
    */
    virtual bool Startup() = 0;
    virtual bool Shutdown() = 0;

	/** 
	 *  包的名字
	 *  @return std::string.
	*/
	virtual std::string Name() = 0;

	/** 
	 *  通知事件，实现者根据type进行static_cast
	 *  @param[in] type.
	 *  @param[in] data.
	 *  @return void.
	*/
	virtual void Notify(EPackageNotify type, const void* data) = 0;

	//只允许管理器调用
private:
	void set_info(const PackageInfo& info)
	{
		m_info = info;
	}
	PackageInfo get_info()const
	{
		return m_info;
	}

private:
	PackageInfo m_info;
};

}

#endif // IPACKAGE_H_

