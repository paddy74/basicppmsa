#include "NetworkUtils.hpp"

namespace basicppmsa::base
{
HostInetInfo NetworkUtils::queryHostInetInfo()
{
    boost::asio::io_service ios;
    boost::asio::ip::tcp::resolver resolver(ios);
    boost::asio::ip::tcp::resolver::query query(
        boost::asio::ip::host_name(), "");

    return resolver.resolve(query);
}

std::string NetworkUtils::hostIP(unsigned short family)
{
    HostInetInfo hostInetInfo = queryHostInetInfo();
    boost::asio::ip::tcp::resolver::iterator end;
    while (hostInetInfo != end)
    {
        boost::asio::ip::tcp::endpoint ep = *hostInetInfo++;
        sockaddr sa = *ep.data();
        if (sa.sa_family == family) return ep.address().to_string();
    }

    return nullptr;
}

}  // namespace basicppmsa::base
