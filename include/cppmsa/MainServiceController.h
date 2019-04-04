#pragma once

#include "../src/base/BasicController.h"  // TODO:


namespace cppmsa
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
class MainServiceController
: public base::BasicController,
         base::core::Controller
{
public:
    // Constructors
    MainServiceController() : base::BasicController() {}
    ~MainServiceController() {}

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

    /**
     * @brief Initialize REST operation handlers
     *
     */
    void initRestOpHandlers() override
    {
        _listener.support(web::http::methods::GET, std::bind(&MainServiceController::handleGet, this, std::placeholders::_1));
        _listener.support(web::http::methods::PUT, std::bind(&MainServiceController::handlePut, this, std::placeholders::_1));
        _listener.support(web::http::methods::POST, std::bind(&MainServiceController::handlePost, this, std::placeholders::_1));
        _listener.support(web::http::methods::DEL, std::bind(&MainServiceController::handleDelete, this, std::placeholders::_1));
        _listener.support(web::http::methods::PATCH, std::bind(&MainServiceController::handlePatch, this, std::placeholders::_1));
    }

protected:
    /**
     * @brief HTTP method not implemented
     *
     * @param method The HTTP method that is not implemented
     * @return web::json::value
     *
     * Usage:
     * ------
     * web::http::methods method;
     * message.reply(web::http::status_codes::NotImplemented, responseNotImpl(method));
     */
    web::json::value responseNotImpl(web::http::method const & method) const
    {
        auto response = web::json::value::object();
        response["serviceName"] = web::json::value::string("CppMSA");
        response["http_method"] = web::json::value::string(method);

        return response;
    }
};

}
