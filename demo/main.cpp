#include "package_mgr.h"

int main(int argc, const char* argv[])
{
    packagemgr::packagemgr_instance::instance()->Startup();
    packagemgr::packagemgr_instance::instance()->Shutdown();

    return 0;
}
