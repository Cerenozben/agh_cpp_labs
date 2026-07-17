#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

class Watchdog
{
public:
    Watchdog(unsigned int timeout_ms) :
            start_time_(std::chrono::system_clock::now()),
            timeout_(timeout_ms),
            thread_(std::make_unique<std::thread>(&Watchdog::guard_dog, this))
    {}

    void terminationTask()
    {
        uint8_t *mem = nullptr;
        *mem = 0xff;  // instant Segfault - your code hangs - this kill process
    }

    ~Watchdog()
    {
        running_ = false;
        thread_->join();
    };

private:
    void guard_dog()
    {
        while (running_)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            {
                if ((std::chrono::system_clock::now() - start_time_).count() / 1000000 > timeout_)
                {
                    running_ = false;
                    terminationTask();
                    break;
                }
            }
        }
    }

private:
    std::chrono::system_clock::time_point start_time_;
    unsigned int timeout_;
    std::unique_ptr<std::thread> thread_;
    std::atomic<bool> running_ = true;
};
