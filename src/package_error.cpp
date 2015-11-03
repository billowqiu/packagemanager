#include "package_error.h"

namespace packagemgr
{

const char* PackageError::getErrorString(ErrorType errorCode)
{
    static const char* errorTab[] =
    {
        /* 0*/"no error",
        /* 1*/"load library fail",
        /* 2*/"get 'packageLoad' func fail",
        /* 3*/"get 'packageUnload' func fail",
        /* 4*/"invoke 'packageLoad' func fail",
        /* 5*/"invoke 'packageUnload' func fail",
        /* 6*/"invoke package 'startup' func fail",
        /* 7*/"package has already loaded",
        /* 8*/"package has not found",
        /* 9*/"package dynamic_cast fail",
        /* 10*/"package config init fail",
        /* 11*/"package config load fail",
    };

    int errorIndex = -1 * (int)errorCode;
    if (0 > errorIndex || errorIndex >= (int)(sizeof(errorTab)/sizeof(errorTab[0])))
    {
        return errorTab[0];
    }
    else
    {
        return errorTab[errorIndex];
    }
}

}
