#include <basicppmsa/InterruptHandler.hpp>
#include <basicppmsa/MainServiceController.hpp>
#include <basicppmsa/RuntimeUtils.hpp>

int main()
{
    basicppmsa::InterruptHandler::hookSIGINT();

    basicppmsa::MainServiceController server;
    server.setEndpoint("http://host_auto_ip4:6502/basicppmsa/api");

    basicppmsa::RuntimeUtils::printStackTrace();

    return 0;
}
