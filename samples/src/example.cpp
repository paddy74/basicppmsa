#include <msabase/InterruptHandler.hpp>
#include <msabase/MainServiceController.hpp>
#include <msabase/RuntimeUtils.hpp>

int main()
{
    // Hook on the SIGINT interrupt
    msabase::InterruptHandler::hookSIGINT();

    // Create and initialize the service at the endpoint
    msabase::MainServiceController server;
    server.setEndpoint("http://host_auto_ip4:6502/msabase/api");

    try
    {
        // Initialize the thread pool used by pplx and start accepting network
        //  connections
        server.accept().wait();
        std::cout << "C++ Microservice now listening for requests at: "
                  << server.endpoint() << std::endl;

        // Prevent the process from leaving until SIGINT
        msabase::InterruptHandler::waitForUserInterrupt();

        // Shutdown the service and wait for all threads to finish
        server.shutdown().wait();
    }
    catch (std::exception const & e)
    {
        std::cerr << "Error: " << std::endl;
    }
    catch (...)
    {
        msabase::RuntimeUtils::printStackTrace();
    }

    return 0;
}
