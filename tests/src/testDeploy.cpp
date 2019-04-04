#include <cppmsa/RuntimeUtils.h>
#include <cppmsa/InterruptHandler.h>
#include <cppmsa/MainServiceController.h>


int main(int argc, const char * argv[])
{
    cppmsa::InterruptHandler::hookSIGINT();

    cppmsa::MainServiceController server;
    server.setEndpoint("http://host_auto_ip4:6502/cppmsa/api");

    try
    {
        server.accept().wait();
        std::cout << "C++ Microservice now listening for requests at: "
            << server.endpoint() << std::endl;

        cppmsa::InterruptHandler::waitForUserInterrupt();

        server.shutdown().wait();
    }
    catch (std::exception const & e)
    {
        std::cerr << "Error: " << std::endl;
    }
    catch (...)
    {
        cppmsa::RuntimeUtils::printStackTrace();
    }

    return 0;
}
