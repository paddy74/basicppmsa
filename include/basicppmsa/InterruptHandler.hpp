#pragma once

#include <signal.h>

#include <condition_variable>
#include <iostream>
#include <mutex>

static std::condition_variable _condition;
static std::mutex _mutex;

namespace cppmsa
{
/**
 * @brief Handle when the user types Ctrl+C on the terminal when the service is
 * running.
 *
 */
class InterruptHandler
{
public:
    /**
     * @brief Hook on the SIGINT interrupt to handle the Ctrl+C
     *
     */
    static void hookSIGINT() { signal(SIGINT, handleUserInterrupt); }

    /**
     * @brief Handle when the user signals to kill the process with SIGINT
     *
     * @param signal
     */
    static void handleUserInterrupt(int signal)
    {
        if (signal == SIGINT)
        {
            std::cout << "SIGINT trapped ..." << '\n';
            _condition.notify_one();
        }
    }

    static void waitForUserInterrupt()
    {
        std::unique_lock<std::mutex> lock{_mutex};
        _condition.wait(lock);
        std::cout << "User has signaled to interrupt program..." << '\n';
        lock.unlock();
    }
};

}  // namespace cppmsa
