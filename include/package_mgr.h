#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <boost/noncopyable.hpp>

#include "common_define.h"
#include "package_if.h"
#include "util.h"
#include "package_error.h"

namespace packagemgr
{

class PackageManager : public boost::noncopyable
{
public:
    PackageManager();
	~PackageManager();
	/** 
	 *  包启动/停止
	 *  @return bool.
	*/
    PackageError::ErrorType Startup();
	PackageError::ErrorType Shutdown();
    /** 
     *  设置用户自定的数据，具体格式用户自己cast
     *  @param[in] data.
     *  @return void.
    */
    void set_user_data(const void* data);
    const void* user_data()const;

	/** 
	 *  给定包的路径，加载到进程中
	 *  @param[in] file.
	 *  @param[in/out] package_name.
	 *  @return bool.
	*/
    PackageError::ErrorType AddPackage(const std::string& file, std::string& package_name);
	/** 
	 *  按包名删除
	 *  @param[in] package_name.
	 *  @return bool.
	*/
	PackageError::ErrorType DelPackage(const std::string& package_name);
	/** 
	 *  按包名获取相应的包接口
	 *  @param[in] package_name.
	 *  @param[in/out] package.
	 *  @return bool.
	*/
	template <typename T>
	PackageError::ErrorType GetPackage(const std::string& package_name, T* &package)
	{
		package_map::iterator it = m_packages_map.find(package_name);
		if (it == m_packages_map.end())
		{
            return PackageError::PACKAGE_ERR_PACKAGE_NOT_FOUND;
		}

		package = dynamic_cast<T*>(it->second);
		if( package == NULL )
        {
            return PackageError::PACKAGE_ERR_CAST_INTERFACE_FAIL;
        }

        return PackageError::PACKAGE_SUCCESS;
	}

private:
	/** 在标准80列的屏幕上输出启动和关闭信息.
	 *
	 * 在包启动和关闭时，根据运行的结果打印出相应的信息.
	 *
	 *	@param[in] sname 服务名称.
	 *	@param[in] proc  启动或关闭过程.
	 *	@param[in] isSuccessed 执行结果.
	 */
	static void PrintMsg( const std::string &sname, const std::string &proc, bool result );

private:
	typedef std::unordered_map<std::string, IPackage*> package_map;
	package_map m_packages_map;
	//用于在关闭程序时按照包加载顺序进行逆序卸载，使用reverse_iterator
	typedef std::vector<IPackage*> package_vec;
	package_vec m_packages_vec;

    //用户自定义数据，目前保持为const属性
    const void* m_user_data;
};

typedef Singleton<PackageManager> packagemgr_instance;

}

#endif // PACKAGEMANAGER_H

