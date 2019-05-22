#include "BasicController.hpp"

#include "NetworkUtils.hpp"

namespace cppmsa::base
{
// Constructors

BasicController::BasicController() {}
BasicController::~BasicController() {}

// Methods

/**
 * @brief Set the service endpoint where it will listen for requests
 *
 * @param value Passing host_auto_ip4 or host_auto_ip6 auto detects the IP
 * address of the host. Follow with the port and base address of the REST API.
 */
void BasicController::setEndpoint(const std::string & value)
{
    web::uri endpointURI(value);
    web::uri_builder endpointBuilder;

    endpointBuilder.set_scheme(endpointURI.scheme());
    endpointBuilder.set_scheme(endpointURI.scheme());
    if (endpointURI.host() == "host_auto_ip4")
    {
        endpointBuilder.set_host(NetworkUtils::hostIP4());
    }
    else if (endpointURI.host() == "host_auto_ip6")
    {
        endpointBuilder.set_host(NetworkUtils::hostIP6());
    }
    endpointBuilder.set_port(endpointURI.port());
    endpointBuilder.set_path(endpointURI.path());

    _listener = web::http::experimental::listener::http_listener(
        endpointBuilder.to_uri());
}

std::string BasicController::endpoint() const
{
    return _listener.uri().to_string();
}

/**
 * @brief Initialize the thread pool that is used by pplx concurrency runtime
 * and start accepting network connections.
 *
 * @return pplx::task<void> Use with .wait() to let it perform the creation of
 * the thread pool and initialize the acceptor.
 */
pplx::task<void> BasicController::accept()
{
    initRestOpHandlers();
    return _listener.open();
}

/**
 * @brief Shutdown the process.
 *
 * @return pplx::task<void> Use with .wait() to wait for all threads to finish.
 */
pplx::task<void> BasicController::shutdown() { return _listener.close(); }

std::vector<utility::string_t> BasicController::requestPath(
    const web::http::http_request & message)
{
    auto relativePath = web::uri::decode(message.relative_uri().path());
    return web::uri::split_path(relativePath);
}

}  // namespace cppmsa::base
