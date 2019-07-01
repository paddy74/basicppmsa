#pragma once

#include <string>

#include "core/stdDef.hpp"

namespace basicppmsa::base
{
using HostInetInfo = boost::asio::ip::tcp::resolver::iterator;

class NetworkUtils
{
public:
    /* Public static member methods */

    /**
     * @brief Gets ths host IP4 string formatted.
     *
     * @return std::string
     */
    static std::string hostIP4();

    /**
     * @brief Gets the host IP6 string formatted.
     *
     * @return std::string
     */
    static std::string hostIP6();

    /**
     * @brief Gets the current host name.
     *
     * @return std::string
     */
    static std::string hostName();

private:
    /* Private static member methods */

    /**
     * @brief
     *
     * @return HostInetInfo
     */
    static HostInetInfo queryHostInetInfo();

    /**
     * @brief
     *
     * @param family
     * @return std::string
     */
    static std::string hostIP(unsigned short family);
};

}  // namespace basicppmsa::base
