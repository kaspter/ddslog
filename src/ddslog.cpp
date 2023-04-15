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


extern "C" {

void ddslog_init(int kind, const char* filename)
{
    if (filename) {
        // use FileConsumer
        // First remove previous executions file
        std::remove(filename);
        Log::ClearConsumers();
        Log::RegisterConsumer(std::unique_ptr<LogConsumer>(new FileConsumer(filename)));
    }
    // Wait till the queues are empty then add new LogConsumer
    Log::Flush();
    Log::RegisterConsumer(std::unique_ptr<LogConsumer>(new StdoutConsumer()));
    Log::SetVerbosity(static_cast<Log::Kind>(kind));
}


void ddslog_exit(void)
{
    // Wait till the queues are empty
    Log::Flush();

    Log::Reset();
    Log::KillThread();
}

void ddslog_kind(int kind)
{
    Log::SetVerbosity(static_cast<Log::Kind>(kind));
}

bool ddslog_kind_enabled(int kind)
{
    return Log::GetVerbosity() >= static_cast<Log::Kind>(kind);
}

void ddslog_printf(int kind, const char *category, const char *function, int line, const char *const fmt, ...)
{
    auto         temp   = std::vector<char>{};
    auto         length = std::size_t{128};
    std::va_list args;
    while (temp.size() <= length) {
        temp.resize(length + 1);
        va_start(args, fmt);
        const auto status = std::vsnprintf(temp.data(), temp.size(), fmt, args);
        va_end(args);
        length = static_cast<std::size_t>(status);
    }
    Log::QueueLog(temp.data(), Log::Context{__FILE__, line, function, category}, static_cast<Log::Kind>(kind));
}

} // extern "C"

} // namespace ddslog
