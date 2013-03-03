#ifndef PACKAGE_ERROR_H
#define PACKAGE_ERROR_H

namespace packagemgr
{
class PackageError
{
public:
    enum ErrorType
    {
        PACKAGE_SUCCESS = 0,
        PACKAGE_ERR_SYSTEM_LOAD_FAIL =  1,
        PACKAGE_ERR_GET_LOAD_FUN_FAIL = 2,
        PACKAGE_ERR_GET_UNLOAD_FUN_FAIL = 3,
        PACKAGE_ERR_INVOKE_LOAD_FUN_FAIL =4,
        PACKAGE_ERR_INVOKE_UNLOAD_FUN_FAIL =5,
        PACKAGE_ERR_PACKAGE_STARTUP_FAIL =6,
        PACKAGE_ERR_PACKAGE_HAS_LOADED = 7,
        PACKAGE_ERR_PACKAGE_NOT_FOUND = 8,
        PACKAGE_ERR_CAST_INTERFACE_FAIL = 9,
        PACKAGE_ERR_CONFIG_INIT_FAIL = 10,
        PACKAGE_ERR_CONFIG_LOAD_FAIL = 11,
    };

public:
    static const char* getErrorString(ErrorType errorCode);
};
}

#endif // PACKAGE_ERROR_H
