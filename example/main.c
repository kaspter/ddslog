


#include <ddslog.h>



#define TAG cLogTest



int main()
{
    ddslog_init(Kind_Info, "ddslog_in_c.log");

    int i = 2;
    logInfoF(TAG, "ddslog Info asdsa %d---FileConsumer", i);

    ddslog_exit();
}
