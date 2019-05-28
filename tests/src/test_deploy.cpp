#include <basicppmsa/InterruptHandler.hpp>
#include <basicppmsa/MainServiceController.hpp>
#include <basicppmsa/RuntimeUtils.hpp>

int main()
{
    basicppmsa::InterruptHandler::hookSIGINT();

    basicppmsa::MainServiceController server;

    return 0;
}
