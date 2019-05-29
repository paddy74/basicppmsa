#include <basicppmsa/InterruptHandler.hpp>
#include <basicppmsa/MainServiceController.hpp>
#include <basicppmsa/RuntimeUtils.hpp>

int main()
{
    basicppmsa::InterruptHandler::hookSIGINT();

    basicppmsa::MainServiceController server;
    server.setEndpoint("http://host_auto_ip4:6502/basicppmsa/api");

    try
    {
        server.accept().wait();
        std::cout << "C++ Microservice now listening for requests at: "
                  << server.endpoint() << std::endl;

        basicppmsa::InterruptHandler::waitForUserInterrupt();

        server.shutdown().wait();
    }
    catch (std::exception const & e)
    {
        std::cerr << "Error: " << std::endl;
    }
    catch (...)
    {
        basicppmsa::RuntimeUtils::printStackTrace();
    }

    return 0;
}