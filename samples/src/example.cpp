#include <basicppmsa/InterruptHandler.hpp>
#include <basicppmsa/MainServiceController.hpp>
#include <basicppmsa/RuntimeUtils.hpp>

int main()
{
    // Hook on the SIGINT interrupt
    basicppmsa::InterruptHandler::hookSIGINT();

    // Create and initialize the service at the endpoint
    basicppmsa::MainServiceController server;
    server.setEndpoint("http://host_auto_ip4:6502/basicppmsa/api");

    try
    {
        // Initialize the thread pool used by pplx and start accepting network
        //  connections
        server.accept().wait();
        std::cout << "C++ Microservice now listening for requests at: "
                  << server.endpoint() << std::endl;

        // Prevent the process from leaving until SIGINT
        basicppmsa::InterruptHandler::waitForUserInterrupt();

        // Shutdown the service and wait for all threads to finish
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
