#include "package_mgr.h"
#include <iostream>
#include <cassert>
#include "config.h"

const char* g_szConfig_file = "package_config.xml";

const std::string MSG_STR_STARTUP	= "Startup";
const std::string MSG_STR_SHUTDOWN	= "Shutdown";
const std::string MSG_STR_OK		= "[  OK  ]";
const std::string MSG_STR_FAILED	= "[ FAIL ]";

namespace packagemgr
{

PackageManager::PackageManager():
m_user_data(NULL)
{
}

PackageManager::~PackageManager()
{
}

PackageError::ErrorType PackageManager::Startup()
{
    if(!Config::Load(g_szConfig_file))
    {
        return PackageError::PACKAGE_ERR_CONFIG_LOAD_FAIL;
    }

	for (uint32_t i=0; i<Config::package_configs_.size(); ++i)
	{
		//加载包
		std::string package_name;
        PackageError::ErrorType ret = AddPackage(Config::package_configs_[i].path, package_name);
        PrintMsg(package_name, MSG_STR_STARTUP, ret == PackageError::PACKAGE_SUCCESS);
	}

    return PackageError::PACKAGE_SUCCESS;
}

PackageError::ErrorType PackageManager::AddPackage(const std::string& file, std::string& package_name)
{
	//包对应的二进制句柄
	package_handler handle;

#ifndef _WIN32
	handle = PM_LOAD_LIBRARY(file.c_str());
#else
	handle = LoadLibraryEx(file.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);
#endif

	if(!handle)
	{
		std::cerr << "load package " << file << " failed : " << PM_GET_ERROR_STRING() << std::endl;
        return PackageError::PACKAGE_ERR_SYSTEM_LOAD_FAIL;
	}
#ifdef _WIN32
	// Reload dll with references resolved...
	FreeLibrary(handle);
	handle = PM_LOAD_LIBRARY(file.c_str());
	if(!handle)
	{
		std::cerr << "load package " << file << "failed : " << PM_GET_ERROR_STRING() << std::endl;
        return PackageError::PACKAGE_ERR_SYSTEM_LOAD_FAIL;
	}
#endif
	//获取包加载/卸载函数符号
	PACKAGE_LOAD load_func = (PACKAGE_LOAD)PM_GET_ADDRESS(handle, "packageLoad");
	if (!load_func)
	{
		std::cerr << "get package " << file << " 'packageLoad' func failed : " << PM_GET_ERROR_STRING() << std::endl;
		PM_UNLOAD_LIBRARY(handle);
        return PackageError::PACKAGE_ERR_GET_LOAD_FUN_FAIL;
	}

	PACKAGE_UNLOAD unload_func = (PACKAGE_UNLOAD)PM_GET_ADDRESS(handle, "packageUnload");
	if (!unload_func)
	{
		std::cerr << "get package " << file << " 'packageUnload' func failed : " << PM_GET_ERROR_STRING() << std::endl;
		PM_UNLOAD_LIBRARY(handle);
        return PackageError::PACKAGE_ERR_GET_UNLOAD_FUN_FAIL;
	}
	//调用包的加载函数，加载失败则卸载包
	IPackage* package = load_func(this);
	if (!package)
	{
		std::cerr << "invoke package " << file << " 'packageLoad' func failed" << std::endl;
        PM_UNLOAD_LIBRARY(handle);
        return PackageError::PACKAGE_ERR_INVOKE_LOAD_FUN_FAIL;
	}
	else
	{
		//启动包服务，包开发者必须保证其启动的正确性
		bool ret = true;
		ret = package->Startup();
		if (!ret)
		{
			PM_UNLOAD_LIBRARY(handle);
            return PackageError::PACKAGE_ERR_PACKAGE_STARTUP_FAIL;
		}
		//添加到包管理容器
		package->set_info(IPackage::PackageInfo(handle, load_func, unload_func));
		package_name = package->Name();

		//防止重复加载
		package_map::iterator it = m_packages_map.find(package_name);
		if (it != m_packages_map.end())
		{
            std::cerr << file << " has already loaded" << std::endl;
            PM_UNLOAD_LIBRARY(handle);
            return PackageError::PACKAGE_ERR_PACKAGE_HAS_LOADED;
		}
		m_packages_map.insert(std::make_pair(package_name, package));
		m_packages_vec.push_back(package);
	}

    return PackageError::PACKAGE_SUCCESS;
}

PackageError::ErrorType PackageManager::Shutdown()
{
	//逆序删除，以将包之间的依赖影响减小
	for ( package_vec::reverse_iterator rit = m_packages_vec.rbegin(); rit != m_packages_vec.rend(); ++rit)
	{
		if ( *rit )
		{
			//关闭包服务，包开发者实现之
			bool ret = (*rit)->Shutdown();
			PrintMsg((*rit)->Name(), MSG_STR_SHUTDOWN, ret);
            //ToDO,调用package的unload_func
            IPackage::PackageInfo pi = (*rit)->get_info();
            if (pi.m_packageUnload)
            {
                pi.m_packageUnload();
            }
			//从进程中卸载
			PM_UNLOAD_LIBRARY((*rit)->get_info().m_handle);
		}
	}
	//由于容器的erase操作不支持reverse_iterator，放到最后直接清空吧
	m_packages_vec.clear();
	m_packages_map.clear();

    return PackageError::PACKAGE_SUCCESS;
}

PackageError::ErrorType PackageManager::DelPackage( const std::string& package_name)
{
	package_map::iterator itm = m_packages_map.find(package_name);
	if (itm == m_packages_map.end())
	{
		return PackageError::PACKAGE_ERR_PACKAGE_NOT_FOUND;
	}

	//关闭包服务，包开发者提供
	itm->second->Shutdown();
	//从进程中卸载
	PM_UNLOAD_LIBRARY(itm->second->get_info().m_handle);
	//从包管理容器中删掉
	m_packages_map.erase(itm);

	for(package_vec::iterator itv = m_packages_vec.begin(); itv!=m_packages_vec.end(); ++itv)
	{
		if ((*itv)->Name() == package_name)
		{
			m_packages_vec.erase(itv);
			break;
		}
	}

    return PackageError::PACKAGE_SUCCESS;
}


void PackageManager::set_user_data( const void* data )
{
    m_user_data = data;
}

const void* PackageManager::user_data() const
{
    return m_user_data;
}

void PackageManager::PrintMsg( const std::string &sname, const std::string &proc, bool result )
{
	std::string lineMsg = sname;

	if ( sname.size() < 60u )
	{
		for ( size_t i = 0u; i < 60u - sname.size(); ++i )
		{
			lineMsg += ' ';
		}
	}

	lineMsg += proc;

	if ( proc.size() < 10u )
	{
		for ( size_t i = 0u; i < 10u - proc.size(); ++i )
		{
			lineMsg += ' ';
		}
	}
	if ( result )
	{
		lineMsg += MSG_STR_OK;
	}
	else
	{
		lineMsg += MSG_STR_FAILED;
	}

	std::cout << lineMsg << std::endl;
}

}

