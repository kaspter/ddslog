/*
 * Copyright (C) 2019 Kaspter Ju <camus@rtavs.com>
 * SPDX-License-Identifier: Apache-2.0
 */

//#define LOG_NO_ERROR

#include <ddslog.h>

#include "example.hpp"

using namespace ddslog;

#define TAG LogTest

#define AML_LOGI(x) logI(TAG, x)
#define AML_LOGD(x) logI(TAG, x)
#define AML_LOGW(x) logW(TAG, x)
#define AML_LOGE(x) logE(TAG, x)

int main()
{
    // use FileConsumer
    // First remove previous executions file
    std::remove("file_consumer.log");
    Log::ClearConsumers();
    Log::RegisterConsumer(std::unique_ptr<LogConsumer>(new FileConsumer("file_consumer.log")));


    // log verbosity runtime setting
    Log::SetVerbosity(Log::Info);
    Log::ReportFilenames(true);

    logE(TAG, "This should be logged");
    logW(TAG, "This should be logged too!");
    logI(TAG, "This should be logged too!");
    AML_LOGD("This should be logged too too!");


    int i = 2;
    logInfoF("123", "Info asdsa %d---FileConsumer", i);
    logWarnF("123", "Warn asdsa %d---FileConsumer", i);
    logErrorF("123", "Error asdsa %d---FileConsumer", i);


    // Wait till the queues are empty then add new LogConsumer
    Log::Flush();
    Log::RegisterConsumer(std::unique_ptr<LogConsumer>(new StdoutConsumer()));

    LogABB();

    logInfoF("321", "Info asdsa %d---FileConsumer + StdoutConsumer", i);
    logWarnF("321", "Warn asdsa %d---FileConsumer + StdoutConsumer", i);
    logErrorF("321", "Error asdsa %d---FileConsumer + StdoutConsumer", i);

    Log::SetVerbosity(Log::Warning);
    logE(TAG, "This should be logged");
    logW(TAG, "This should be logged too!");
    logI(TAG, "If you're seeing this info, something went wrong");

#if 1
    Log::SetVerbosity(Log::Error);
    logE(TAG, "This should be logged");
    logW(TAG, "If you're seeing this warning, something went wrong");
    logI(TAG, "If you're seeing this info, something went wrong");

    // log __file__/__func__/__line__


    // Log::SetVerbosity(Log::Info);
    logE(TAG, "This should be logged");
    logW(TAG, "This should be logged too!");
    logI(TAG, "This should be logged too too!");

    // Log::ReportFilenames(false);

    // log category filter
    Log::SetVerbosity(Log::Info);
    Log::SetCategoryFilter(std::regex("(Good)"));
    logE(GoodCategory, "This should be logged because my regex filter allows for it");
    logE(BadCategory, "If you're seeing this, something went wrong");
    logW(EvenMoreGoodCategory, "This should be logged too!");

#endif
    // Wait till the queues are empty
    Log::Flush();

    Log::Reset();
    Log::KillThread();


    // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    // delete localConsumer;
}
