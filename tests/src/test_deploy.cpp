#include <msabase/InterruptHandler.hpp>
#include <msabase/MainServiceController.hpp>
#include <msabase/RuntimeUtils.hpp>

int main()
{
    msabase::InterruptHandler::hookSIGINT();

    msabase::MainServiceController server;
    server.setEndpoint("http://host_auto_ip4:6502/msabase/api");

    msabase::RuntimeUtils::printStackTrace();

    return 0;
}
