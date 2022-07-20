//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//


#ifndef _DDSLOG_H_
#define _DDSLOG_H_

#ifdef __cplusplus

#include <cstdarg>    // va_start, va_end, std::va_list
#include <cstddef>    // std::size_t
#include <stdexcept>  // std::runtime_error
#include <vector>     // std::vector

#include <fastdds/Colors.hpp>
#include <fastdds/FileConsumer.hpp>
#include <fastdds/Log.hpp>
#include <fastdds/StdoutConsumer.hpp>
#include <fastdds/StdoutErrConsumer.hpp>


namespace ddslog {

using Log            = eprosima::fastdds::dds::Log;
using LogConsumer    = eprosima::fastdds::dds::LogConsumer;
using FileConsumer   = eprosima::fastdds::dds::FileConsumer;
using StdoutConsumer = eprosima::fastdds::dds::StdoutConsumer;
using StdoutErrConsumer = eprosima::fastdds::dds::StdoutErrConsumer;


#define logI(cat, msg) logInfo_(cat, msg)
//! Logs a warning. Disable reporting through Log::SetVerbosity or define LOG_NO_WARNING
#define logW(cat, msg) logWarning_(cat, msg)
//! Logs an error. Disable reporting through define LOG_NO_ERROR
#define logE(cat, msg) logError_(cat, msg)
} // namespace ddslog

#endif // __cplusplus



#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

enum Kind
{
    Kind_Error,
    Kind_Warning,
    Kind_Info,
};

//! C style logs
#define logInfoF(cat, fmt, ...) logInfoF_(cat, fmt, __VA_ARGS__)
#define logWarnF(cat, fmt, ...) logWarnF_(cat, fmt, __VA_ARGS__)
#define logErrorF(cat, fmt, ...) logErrorF_(cat, fmt, __VA_ARGS__)

void ddslog_init(int kind, const char* filename);
void ddslog_exit(void);
void ddslog_printf(int kind, const char *category, const char *function, int line, const char *const fmt, ...);

bool ddslog_kind_enabled(int kind);

#define logInfoF_(cat, fmt, ...)                                                                        \
    {                                                                                                   \
        if (ddslog_kind_enabled(Kind_Info))                                                             \
        {                                                                                               \
            ddslog_printf(Kind_Info, #cat, __func__, __LINE__, fmt, __VA_ARGS__);                       \
        }                                                                                               \
    }


#define logWarnF_(cat, fmt, ...)                                                                        \
    {                                                                                                   \
        if (ddslog_kind_enabled(Kind_Warning))                                                          \
        {                                                                                               \
            ddslog_printf(Kind_Warning, #cat, __func__, __LINE__, fmt, __VA_ARGS__);                    \
        }                                                                                               \
    }

#define logErrorF_(cat, fmt, ...)                                                                       \
    {                                                                                                   \
        if (ddslog_kind_enabled(Kind_Error))                                                            \
        {                                                                                               \
            ddslog_printf(Kind_Error, #cat, __func__, __LINE__, fmt, __VA_ARGS__);                      \
        }                                                                                               \
    }

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
