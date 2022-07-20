


#include <atomic>
#include <chrono>
#include <cstdio>
#include <thread>
#include <vector>


#include <ddslog.h>

using namespace ddslog;


/* Returns microseconds since epoch */
uint64_t timestamp_now()
{
    return std::chrono::high_resolution_clock::now().time_since_epoch() / std::chrono::microseconds(1);
}

void ddslog_benchmark()
{
    int const         iterations = 100000;
    char const *const benchmark  = "benchmark";
    uint64_t          begin      = timestamp_now();
    for (int i = 0; i < iterations; ++i) {
        //std::cout << "Logging " << benchmark << i << 0 << 'K' << -42.42;
        logInfoF(TAG, "Logging %s  %d %d %d %f", benchmark, i, 0, 'K', -42.42);
    }
    uint64_t end         = timestamp_now();
    long int avg_latency = (end - begin) * 1000 / iterations;

    printf("\tAverage ddslog Latency = %ld nanoseconds\n", avg_latency);
}

template <typename Function>
void run_benchmark(Function &&f, int thread_count)
{
    printf("Thread count: %d\n", thread_count);
    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(f);
    }
    for (int i = 0; i < thread_count; ++i) {
        threads[i].join();
    }
}

int main()
{
    // use FileConsumer
    // First remove previous executions file
    //std::remove("file_consumer.log");
    //Log::ClearConsumers();
    //Log::RegisterConsumer(std::unique_ptr<LogConsumer>(new FileConsumer("file_consumer.log")));


    // log verbosity runtime setting
    Log::SetVerbosity(Log::Info);
    Log::ReportFilenames(false);


    for (auto threads : {1, 2, 3, 4, 5})
        run_benchmark(ddslog_benchmark, threads);


    // Wait till the queues are empty
    Log::Flush();

    Log::Reset();
    Log::KillThread();


    // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    // delete localConsumer;
}
