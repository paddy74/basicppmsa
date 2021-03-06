#pragma once

#include <execinfo.h>
#include <unistd.h>

namespace msabase
{
/**
 * @brief Print the stack trac when an unexpected exception occurs
 *
 */
class RuntimeUtils
{
public:
    static void printStackTrace()
    {
        const int MAX_CALLSTACK = 100;
        void * callstack[MAX_CALLSTACK];
        int frames;

        // get void*'s for all entries on the stack...
        frames = backtrace(callstack, MAX_CALLSTACK);

        // print out all the frames to stderr...
        backtrace_symbols_fd(callstack, frames, STDERR_FILENO);
    }
};

}  // namespace msabase
