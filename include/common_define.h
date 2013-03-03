#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H
#include <string>
#include <stdint.h>

#ifndef interface
	#define interface struct
#endif

#ifdef _WIN32
#	include <Windows.h>
#	ifdef BUILDING_PACKAGE_LIB
#		define PACKAGE_API
#	else
#		define PACKAGE_API __declspec(dllexport)
#	endif
	typedef HMODULE package_handler;
#else
#	ifdef BUILDING_PACKAGE_LIB
#		define PACKAGE_API
#	else
#		define PACKAGE_API __attribute__ ((visibility("default")))
#	endif
	typedef void* package_handler;
#endif //WIN32

extern std::string translateError(int aError);

#ifdef _WIN32
#	include <Windows.h>
#	include <tchar.h>
#	define PACKAGE_EXT _T(".dll")
#	define PM_LOAD_LIBRARY(filename) LoadLibrary(filename)
#	define PM_UNLOAD_LIBRARY(lib) FreeLibrary(lib)
#	define PM_GET_ADDRESS(lib, name) GetProcAddress(lib, name)
#	define PM_GET_ERROR_STRING() translateError(GetLastError())
#else
#	include <dlfcn.h>
#	define PACKAGE_EXT ".so"
#	define PM_LOAD_LIBRARY(filename) ::dlopen(filename, RTLD_LAZY | RTLD_GLOBAL)
#	define PM_UNLOAD_LIBRARY(lib) ::dlclose(lib)
#	define PM_GET_ADDRESS(lib, name) ::dlsym(lib, name)
#	define PM_GET_ERROR_STRING() ::dlerror()
#endif //WIN32

namespace packagemgr
{
class PackageManager;
interface IPackage;

/**
 * 包加载时由包管理器调用，由包开发者负责创建包的实例
 * 返回值为包的实例，返回NULL表示加载失败
 * 
 *
*/
typedef IPackage* (*PACKAGE_LOAD)(PackageManager*);

/**
 * 包被卸载时调用，由包开发者负责销毁包的实例及清除动作
 */
typedef void (*PACKAGE_UNLOAD)();

#define PACKAGE_DEFINE(packagename)							    \
	extern "C"													\
	{															\
		IPackage* g_package = NULL;								\
		PACKAGE_API IPackage* packageLoad(PackageManager *pm)	\
		{														\
			g_package = new packagename;					    \
			return g_package;									\
		}														\
																\
		PACKAGE_API void packageUnload()						\
		{														\
			if (g_package)										\
			{													\
				delete g_package;								\
				g_package = NULL;								\
			}													\
		}														\
	};				

}

#endif // COMMON_DEFINE_H
