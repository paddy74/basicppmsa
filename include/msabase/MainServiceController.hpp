#pragma once

#include "../src/base/BasicController.hpp"

namespace msabase
{
/**
 * @brief Manages registering handles with the http_listener and provides
 * implementations for the following http_request methods
 *
 * Implemented requests
 * --------------------
 * - GET
 * - PUT
 * - POST
 * - PATCH
 * - DEL
 * - HEAD
 * - OPTIONS
 * - TRACE
 * - CONNECT
 * - MERGE
 */
class MainServiceController : public base::BasicController,
                              base::core::Controller
{
public:
    /* Constructors */

    MainServiceController() : base::BasicController()
    {
        this->serviceName = "C++ REST SDK Service";
    }
    MainServiceController(utility::string_t const & serviceName)
        : base::BasicController()
    {
        this->serviceName = serviceName;
    }
    ~MainServiceController() {}

    /* Public class methods */

    void virtual handleGet(web::http::http_request message) override;
    void virtual handlePut(web::http::http_request message) override;
    void virtual handlePost(web::http::http_request message) override;
    void virtual handlePatch(web::http::http_request message) override;
    void virtual handleDelete(web::http::http_request message) override;
    void virtual handleHead(web::http::http_request message) override;
    void virtual handleOptions(web::http::http_request message) override;
    void virtual handleTrace(web::http::http_request message) override;
    void virtual handleConnect(web::http::http_request message) override;
    void virtual handleMerge(web::http::http_request message) override;

    void initRestOpHandlers() override;

protected:
    /* Protected class variables */

    utility::string_t serviceName;  // The name of the microservice

    /* Protected class methods */

    /**
     * @brief HTTP method not implemented
     *
     * @param method The HTTP method that is not implemented
     * @return web::json::value
     *
     * Usage:
     * ------
     * web::http::methods method;
     * message.reply(web::http::status_codes::NotImplemented,
     * responseNotImpl(method));
     */
    web::json::value responseNotImpl(web::http::method const & method) const;
};

}  // namespace msabase
