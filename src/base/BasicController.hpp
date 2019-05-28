#pragma once

#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>

#include <string>

#include "core/Controller.hpp"

namespace basicppmsa::base
{
/**
 * @brief Provides a wrapper around http_listener and methods to read the
 * endpoint string and decide if the service should determine the host's IP
 * address as IP4, IP6, or a given fixed domain name or IP address
 *
 */
class BasicController
{
public:
    BasicController();
    ~BasicController();

    void setEndpoint(const std::string & value);

    std::string endpoint() const;
    pplx::task<void> accept();
    pplx::task<void> shutdown();

    virtual void initRestOpHandlers() {}

    std::vector<utility::string_t> requestPath(
        const web::http::http_request & message);

protected:
    // Main micro service network endpoint
    web::http::experimental::listener::http_listener _listener;
};

}  // namespace basicppmsa::base
