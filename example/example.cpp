


#include <ddslog.h>

using namespace ddslog;


#define TAG LogABB

int LogABB(void)
{
    uint32_t index = 5;
    logE(TAG, "Locator: " << index << " not present in new list");
    return 0;
}
