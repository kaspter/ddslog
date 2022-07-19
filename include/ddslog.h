#ifndef _DDSLOG_H_
#define _DDSLOG_H_

#include <cstdarg>    // va_start, va_end, std::va_list
#include <cstddef>    // std::size_t
#include <stdexcept>  // std::runtime_error
#include <vector>     // std::vector

#include <fastdds/Colors.hpp>
#include <fastdds/FileConsumer.hpp>
#include <fastdds/Log.hpp>
#include <fastdds/StdoutConsumer.hpp>
#include <fastdds/StdoutErrConsumer.hpp>

enum Kind
{
    Error,
    Warning,
    Info,
};


#define logI(cat, msg) logInfo_(cat, msg)
//! Logs a warning. Disable reporting through Log::SetVerbosity or define LOG_NO_WARNING
#define logW(cat, msg) logWarning_(cat, msg)
//! Logs an error. Disable reporting through define LOG_NO_ERROR
#define logE(cat, msg) logError_(cat, msg)

#define logInfoF_(cat, fmt, ...) logFormatF_(cat, Kind::Info, fmt, __VA_ARGS__)


namespace ddslog {

using Log            = eprosima::fastdds::dds::Log;
using LogConsumer    = eprosima::fastdds::dds::LogConsumer;
using FileConsumer   = eprosima::fastdds::dds::FileConsumer;
using StdoutConsumer = eprosima::fastdds::dds::StdoutConsumer;
using StdoutErrConsumer = eprosima::fastdds::dds::StdoutErrConsumer;

static inline void logFormatF_(const char *category, Kind level, const char *const fmt, ...)
{
    using namespace ddslog;
    auto         temp   = std::vector<char>{};
    auto         length = std::size_t{128};
    Log::Kind   kind = (Log::Kind)level;
    std::va_list args;
    while (temp.size() <= length) {
        temp.resize(length + 1);
        va_start(args, fmt);
        const auto status = std::vsnprintf(temp.data(), temp.size(), fmt, args);
        va_end(args);
        length = static_cast<std::size_t>(status);
    }
    Log::QueueLog(temp.data(), Log::Context{__FILE__, __LINE__, __func__, category}, kind);
}

} // namespace ddslog

#endif