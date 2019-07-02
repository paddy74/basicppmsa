#include "NetworkUtils.hpp"

namespace msabase::base
{
/* Public static member methods */

std::string NetworkUtils::hostIP4() { return NetworkUtils::hostIP(AF_INET); }

std::string NetworkUtils::hostIP6() { return NetworkUtils::hostIP(AF_INET6); }

std::string NetworkUtils::hostName() { return boost::asio::ip::host_name(); }

/* Private static member methods */

HostInetInfo NetworkUtils::queryHostInetInfo()
{
    boost::asio::io_service ios;
    boost::asio::ip::tcp::resolver resolver(ios);
    boost::asio::ip::tcp::resolver::query query(  // TODO: deprecated
        boost::asio::ip::host_name(), "");

    return resolver.resolve(query);  // TODO: deprecated
}

std::string NetworkUtils::hostIP(unsigned short family)
{
    HostInetInfo hostInetInfo = NetworkUtils::queryHostInetInfo();
    boost::asio::ip::tcp::resolver::iterator end;
    while (hostInetInfo != end)
    {
        boost::asio::ip::tcp::endpoint ep = *hostInetInfo++;
        sockaddr sa = *ep.data();
        if (sa.sa_family == family) return ep.address().to_string();
    }

    return nullptr;
}

}  // namespace msabase::base
