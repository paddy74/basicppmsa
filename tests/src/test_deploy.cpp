#include <basicppmsa/InterruptHandler.hpp>
#include <basicppmsa/MainServiceController.hpp>
#include <basicppmsa/RuntimeUtils.hpp>

int main()
{
    cppmsa::InterruptHandler::hookSIGINT();

    cppmsa::MainServiceController server;

    return 0;
}
